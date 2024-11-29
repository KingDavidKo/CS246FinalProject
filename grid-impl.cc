
#include "grid.h"
#include "cell.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

Grid::Grid(): currentBlock {nullptr} { // this is just so we have something there for the block ig
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 11; j++) {
            cells[i][j] = unique_ptr<Cell>{}; // empty unique pointer		
        }
    }
	this->blind = false;


	this->heavy = false; 
	// MAY BE SET TO TRUE FOR TESTING PURPOSES


	this->levelHeavy = false;
	// MAY BE SET TRUE FOR TESTING PURPOSES
}

// sets the current block in the starting position
void Grid::setCurrent(shared_ptr<Block> block) {
    // the last "current block" should alr be in the Blocks vector, so it's safe to reassign the pointer
    currentBlock = block;

    vector<Cell*> blockCells = currentBlock->getCells();
    //currentBlock->setXAnchor(0);
    //currentBlock->setYAnchor(3);
	currentBlock->setAnchors(0,3);
    currentBlock->updateCellCoords(); // Double check it's cell and not grid

    for (int i = 0; i < 4; i++) {
	// if there's something in the cells where we want to place, we can't place the block
        if (cells[blockCells[i]->getGridY()][blockCells[i]->getGridX()]) {
		// if we can't even place a block, game over
		gameOver = true;
		return;
        }
    }
	
    for (int i = 0; i < 4; i++) {
         cells[blockCells[i]->getGridY()][blockCells[i]->getGridX()] = unique_ptr<Cell>(blockCells[i]); // put the cell there, by having the grid point to the cell there
        
     }

    // add the block to our blocks vector
    blocksInGrid.emplace_back(currentBlock);	
}


void Grid::removeBlock(Block * block){
	for (auto it = blocksInGrid.begin(); it != blocksInGrid.end();){
		if (it->get() == block) blocksInGrid.erase(it);
		else ++it;
	}
	// ok we could break after we erase the block from the grid but im not gonna do that just to be sure
}

bool Grid::isGameOver() {
	return gameOver;
}


// in the destructor, we just need to set every block's isDied field to true so they don't increase the score a bunch when they inevitably get deleted
Grid::~Grid(){
	for (auto block : blocksInGrid){ 
		block->setBlockDied(true);	// most likely needs to be .get()	
	}

}

vector<char> Grid::returnState(int n) {
	vector<char> row {};
	for (int i = 0; i<11; i++){
		// if blind is active and we're within rows 3-12, cols 3-9
		if (n+1 >= 3 && n+1 <= 12 && i+1 >= 3 && i+1 <= 9 && blind){
			row.emplace_back('?');
                }

		else if(!cells[n][i]){ // blank cell
			row.emplace_back(' ');
		}
		else{
			
			row.emplace_back(cells[n][i]->getLetter());
		}
	}
	return row;
}


// returns true if move valid on board, false otherwise

// dx = translation amount left or right
// dy = translation down
// CW for clockwise rotation
// CCW for counterclockwise rotation
// remember that positive dx goes right, positive dy goes down
bool Grid::isValidMove(shared_ptr<Block> block, int dx, int dy, bool CW, bool CCW){
    std::vector<std::pair<int, int>> originalInternalCoords;
    for (Cell* cell : block->getCells()) {
        originalInternalCoords.emplace_back(cell->getInternalX(), cell->getInternalY());
		
    }
    int originalAnchorX = block->getXAnchor();
    int originalAnchorY = block->getYAnchor();


	std::vector<std::pair<int, int>> originalGridCoords;
    for (Cell* cell : block->getCells()) {
        originalGridCoords.emplace_back(cell->getGridX(), cell->getGridY());
		
    }

	block->setAnchors(originalAnchorX + dx, originalAnchorY + dy);
	block->updateCellCoords();
	// the cells are not 

    // Apply rotation if specified
    if (CW) {
        block->rotateCW();
    } else if (CCW) {
        block->rotateCCW();
    }

	
    // Validate all cells in the block after translation and/or rotation
    for (Cell* cell : block->getCells()) {
        
		// cell coords post translation or whatever
		// THEIR GRID COORDS WERE ADJUSTED RIGHT AFTER THE IN THE SETANCHORS CALL -- DO NOT ADD DX AND DY HERE

        int new_x = cell->getGridX();
        int new_y = cell->getGridY();



        // Check grid boundaries (left, right, and bottom edges)
        if (new_x < 0 || new_x >= 11 || new_y < 0 || new_y >= 18) {
            // Revert the block to its original state before returning
            block->resetState(originalInternalCoords, originalAnchorX, originalAnchorY);
            return false;
        }

        // check for collisions with existing cells on the grid
		//cout << "new y: " << new_y << "new x:" << new_x << endl;
		//if (cells[new_y][new_x] !=nullptr) cout << cells[new_y][new_x]->getLetter() << endl;
		

		// experiment: !block->containsCoords(new_x, new_y) was removed from the conditional
		pair<int, int> newcoords {new_x, new_y};
		// uses std::find from algorithm library
		bool inOriginal = find(originalGridCoords.begin(), originalGridCoords.end(), newcoords) != originalGridCoords.end();
		// should be checking the original grid coordinates


		// if that cell isn't null and that cell wasn't in the original cell grid coords 
		// (the original cell coords should've been valid)
		
		if (cells[new_y][new_x] != nullptr && !inOriginal) {
			// checks whether that one is null, or if the translated block contains the coords that we want to move in
			
			// if we found a cell that conflicts 


			//cells[new_y][new_x] != nullptr was changed
			// instead compare to an empty unique ptr
	
			//cout << "conflicting cell at coords x: " << new_x <<", y:" << new_y << endl;
            // revert the block to its original state before returning
            block->resetState(originalInternalCoords, originalAnchorX, originalAnchorY);



            return false;
        }
		
    }

	//cout << "move is valid" << endl;
    // revert the block to its original state before returning (no permanent changes during validation)
    block->resetState(originalInternalCoords, originalAnchorX, originalAnchorY);
    return true; // Move and/or rotation is valid


}

// moves a block given translation or rotation
// this should only be used after isValidMove has validated the move
// remember that positive dx goes right, positive dy goes down
void Grid::moveBlock(shared_ptr<Block> b, int dx, int dy, bool CW, bool CCW){
	
	// Step 1: save the old cell grid coords before the block move
	// we're gonna move the unique_ptrs later
    std::vector<std::pair<int, int>> originalGridCoords; // stored as x,y
    for (Cell* cell : b->getCells()) {
       	originalGridCoords.emplace_back(cell->getGridX(), cell->getGridY());
    }
    // moving instead of like releasing now is just memory safer, cause the move ctor is built in
    // also less room for memory leaks

	// ok instead we're gonna release temporarily to transfer over ownership
        
    // Step 2: perform the move or rotation as desired
    if (CW){
	b->rotateCW();
    }
    else if (CCW){
	b->rotateCCW();
    }

    b->setAnchors(b->getXAnchor() + dx, b->getYAnchor() + dy);
    b->updateCellCoords();

    vector<Cell*> blockCells = b->getCells();

    // Step 3: add the Block's cells back to the grid
    // currently the cells are still where they used to be, so we're gonna 

    for (long unsigned int i = 0; i< blockCells.size(); ++i){
		cells[originalGridCoords[i].second][originalGridCoords[i].first].release(); // temporarily release
		// releases ownership without deleting
	}
	
    for (long unsigned int i = 0; i < blockCells.size(); ++i) {

		Cell* cell = blockCells[i];
        int x = cell->getGridX();
        int y = cell->getGridY();

		//cout << "cell " << i << " of current block, with coords x: " << x << ", y: " << y << endl;

		// safely moving the cells from the old coords to the new coords]
		
		
		cells[y][x] = unique_ptr<Cell>(cell);
		//cout << "coords of new cell -- y: " << y << ", x:" << x << endl; 


     }

	 


}

// drop some block (usually the current block but it can vary)
bool Grid::dropBlock(shared_ptr<Block> b){
	
	while(isValidMove(b, 0, 1, false, false)) { // moving one down
		moveBlock(b, 0, 1, false, false); // if you can move the block down one, then move it down one
			
	}
	// go until you can't move it down any more
		


	// check if any lines are cleared -- separate method
	int linescleared = clearFullRows();


	// check if any blocks are dead,
	// if they are, then try to go row by row to drop the blocks of ever cell
	// idk ask about whether this is bonus or not
	// seems tedious to implement, if its bonus then focus on core features
	

	// since we just dropped a block, turn off special actions if they were on
	if (blind) blind = false;
	if (heavy) heavy = false;


	// THE CURRENT BLOCK SHOULD ALREADY BE IN THE BLOCKS VECTOR,
	// SO WE CAN SAFELY SET THE CURRENTBLOCK PTR TO NULLPTR HERE
	
	currentBlock = nullptr; // we dropped the block -- it's no longer the current block
	if (linescleared >= 2) return true;
	else return false;
}



// checks for cleared rows, and moves the blocks down + increments the score appropriately if 
// any rows are cleared
int Grid::clearFullRows(){
	int linesCleared = 0;
	int rows = 18;
	int cols = 11;

	// int rowsLeftToCheck = 4;


	// maybe make it y >= rowsCleared, since if one row cleared then no need to check top row for a clear

	for (int y = rows - 1; y >= 0; --y){ // we check the bottom 4 rows, cause only 4 rows can be cleared a at a time max		
		// each loop iteration checks if the bottom row is full or not
		bool isFull = true;
		for (int x = 0; x < cols; ++x){
			if(!cells[y][x]){
				isFull = false;
				break;
			}
		}
		if (isFull) {
			//cout << "clearing row # " << y << endl;

			for (int x = 0; x < cols; x++){
				

				cells[y][x].reset(); // releases ownership and deletes the Cell
				// via our cell implementation, if one of cells cleared was the last cell of a block, then that block will be deleted and removed from the blocksInGrid vector
			}

			// now let's shift all of the other rows down as well
			for (int moveY = y; moveY > 0; moveY--){
				for(int x = 0; x < cols; ++x) {

					Cell* c = cells[moveY - 1][x].get(); // get the cell pointer
					cells[moveY - 1][x].release(); // release ownership from the previous position of that cell
					cells[moveY][x] = unique_ptr<Cell>(c); // move ownership to the cell right below

					if (cells[moveY][x]){ // it may or may not be null
						cells[moveY][x]->translateGridY(1); // moves the grid_y field down 1 row
						// adjusts the grid_y coord of that cell

						cells[moveY][x]->getParent()->updateAnchorY(); // updates the Y anchor of the block afer that cell was moved down
					}
				}	
			
			}
			// we shouldn't need to release the top-most row here, as std::move should've already made the top row empty	

			linesCleared++;
				
			y++; // we just cleared a line and moves the stuff down, we need to recheck that row to see if the row right above it (which has now been moved into the current row)

		} // end of isFull case
	
	} // end of line clearing for loop
	
	for(auto it = blocksInGrid.begin(); it != blocksInGrid.end();){
		if(it->get()->numCells() == 0) blocksInGrid.erase(it); // if numcells = 0, then erase it from the blocksInGrid vector
		else ++it;
	}



	// update the block anchors for each block	
	for (shared_ptr<Block> block : blocksInGrid){
		block->updateAnchorY();	
	}

	//cout << "lines cleared: " << linesCleared << endl;

	// update the score
	int addedpoints = (linesCleared + level) * (linesCleared + level);
	
	//cout << "number of points to add: " << addedpoints;
	
	addToScore(addedpoints);
	
	//cout << "score: " << score;
	
	return linesCleared;
}
	

// idt we need this
//void Grid::addBlock(Block& b) {}


// mutators and accessors
shared_ptr<Block> Grid::returnCurrentBlock() {
		return currentBlock;
}

// void Grid::setCurrentBlock(shared_ptr<Block> freshBlock) {
// 	currentBlock = freshBlock;
// 	return;
// }

int Grid::getLevel() { return level; }

int Grid::getScore() { return score; }

void Grid::addToScore(int s){
	score += s;

}
void Grid::setLevel(int newlevel){
	level = newlevel;
	if (level >= 3){
		levelHeavy = true;
	}
	if (level == 4){
		centreBlockOn = true;
	}
}



void Grid::setBlind(bool isBlind){
	blind = isBlind;
}
void Grid::setHeavy(bool isHeavy){
	heavy = isHeavy;
}


bool Grid::isBlind() { return blind;}
bool Grid::isHeavy() { return heavy; }
bool Grid::isLevelHeavy() { return levelHeavy; }
