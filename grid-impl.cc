#include "grid.h"
#include "cell.h"
#include <vector>
#include <utility>

using namespace std;

Grid::Grid(): currentBlock {Block(this)} { // this is just so we have something there for the block ig
    rows = 18; // 15 available + 3 reserved
    columns = 11;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cells[i][j] = unique_ptr<Cell>{}; // empty unique pointer		
        }
    }

}

// sets the current block in the starting position
void Grid::setCurrent(Block block) {
    // the last "current block" should alr be in the Blocks vector, so it's safe to reassign the pointer
    currentBlock = &block;

    vector<Cell*> blockCells = block.getCells();
    block.setAnchorX(0);
    block.setAnchorY(3);

    block.updateGridCoords();

    for (int i = 0; i < 4; i++) {
	// if there's something in the cells where we want to place, we can't place the block
        if (cells[blockCells[i]->getGridY()][blockCells[i]->getGridX()]) {
		// if we can't even place a block, game over
		gameOver = true;
		return;
        }
    }

    for (int i = 0; i < 4; i++) {
        cells[blockCells[i]->getGridY()][blockCells[i]->getGridX()] = uniquePtr(blockCells[i]); // put the cell there, by having the grid point to the cell there
        
    }

    // add the block to our blocks vector
    blocksInGrid.emplace_back(currentBlock);	
}

bool Grid::isGameOver() {
	return gameOver;
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
bool Grid::isValidMove(Block* block, int dx, int dy, bool CW, bool CCW){
    std::vector<std::pair<int, int>> originalInternalCoords;
    for (const Cell* cell : block->getCells()) {
        originalInternalCoords.emplace_back(cell->getInternalX(), cell->getInternalY());
    }
    int originalAnchorX = block->getAnchorX();
    int originalAnchorY = block->getAnchorY();

    // Apply rotation if specified
    if (rotateCW) {
        block->rotateCW();
    } else if (rotateCCW) {
        block->rotateCCW();
    }

    // Validate all cells in the block after translation and/or rotation
    for (Cell* cell : block->getCells()) {
        // Calculate the new grid coordinates after translation
        int new_x = cell->getGridX() + dx;
        int new_y = cell->getGridY() + dy;

        // Check grid boundaries (left, right, and bottom edges)
        if (new_x < 0 || new_x >= 11 || new_y < 0 || new_y >= 18) {
            // Revert the block to its original state before returning
            block->resetState(originalCoords, originalAnchorX, originalAnchorY);
            return false;
        }

        // check for collisions with existing cells on the grid
        if (grid[new_y][new_x] != nullptr) {
            // revert the block to its original state before returning
            block->resetState(originalCoords, originalAnchorX, originalAnchorY);
            return false;
        }
    }

    // revert the block to its original state before returning (no permanent changes during validation)
    block->resetState(originalCoords, originalAnchorX, originalAnchorY);
    return true; // Move and/or rotation is valid


}

// moves a block given translation or rotation
// this should only be used after isValidMove has validated the move
// remember that positive dx goes right, positive dy goes down
void Grid::moveBlock(Block* b, int dx, int dy, bool CW, bool CCW){
	
	// Step 1: save the old cell grid coords before the block move
	// we're gonna move the unique_ptrs later
    std::vector<std::pair<int, int>> originalGridCoords; // stored as x,y
    for (const Cell* cell : block->getCells()) {
       	originalGridCoords.emplace_back(cell->getGridX(), cell->getGridY());
    }
    // moving instead of like releasing now is just memory safer, cause the move ctor is built in
    // also less room for memory leaks
        
    // Step 2: perform the move or rotation as desired
    if (CW){
	b->rotateCW();
    }
    else if (CCW){
	b->rotateCCW();
    }

    b->setAnchors(b->getXAnchor + dx, b->getYAnchor() + dy);
    b->updateCellCoords();

    vector<Cell*> cells = b->getCells();

    // Step 3: add the Block's cells back to the grid
    // currently the cells are still where they used to be, so we're gonna use move
     for (int i = 0; i < cells.size(); ++i) {

	Cell* cell = cells[i]
        int x = cell->getGridX();
        int y = cell->getGridY();

	// safely moving the cells from the old coords to the new coords
	grid[y][x] = move(grid[originalGridCoords[i].second][originalGridCoords[i].first]);
     }


}

// drop some block (usually the current block but it can vary)
void Grid::dropBlock(Block b*){
	
	while(isValidMove(b, 0, 1, false, false){ // moving one down
		moveBlock(b, 0, 1, false, false); // if you can move the block down one, then move it down one
			
	}
	// go until you can't move it down any more
	


	// check if any lines are cleared -- separate method
	clearFullRows();	


	// check if any blocks are dead,
	// if they are, then try to go row by row to drop the blocks of ever cell
	// idk ask about whether this is bonus or not
	// seems tedious to implement, if its bonus then focus on core features
	

	// since we just dropped a block, turn off special actions)
	if (blind) blind = false;
	if (heavy) heavy = false;
}


// checks for cleared rows, and moves the blocks down + increments the score appropriately if 
// any rows are cleared
void Grid::clearFullRows(){

}


// idt we need this
//void Grid::addBlock(Block& b) {}


// mutators and accessors


int Grid::getLevel() { return level; }

int Grid::getScore() { return score; }

void Grid::addToScore(int s){
	score += s;

}
void Grid::setLevel(int newlevel){
	level = newlevel;
}



void Grid::setBlind(bool isBlind){
	blind = isBlind;
}
void Grid::setHeavy(bool isHeavy){
	heavy = isHeavy;
}
