#include <string>
#include <vector>
#include "cell.h"
#include "grid.h"
#include "block.h"
#include <memory>
using namespace std;


Block::Block(Grid *g, int x, int y, int levelOfBirth): x_anchor {x}, y_anchor {y}, g {g}, levelOfBirth {levelOfBirth} {
	lifetimeCount = 0;
	blockDied = false;
	// rest of fields don't need to be added cause Block should be abstract	
}

IBlock::IBlock(Grid *g, int x, int y, int levelOfBirth): Block{g, x, y, levelOfBirth} {
	// inititalize the children cell vector
	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	children.push_back(new Cell(3, 3, this));


	// add the letter
	letter= 'I';
}



JBlock::JBlock(Grid *g, int x, int y, int levelOfBirth): Block{g, x, y, levelOfBirth} {

	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	
	letter = 'J';
}

LBlock::LBlock(Grid *g, int x, int y, int levelOfBirth): Block{g, x, y, levelOfBirth} {

	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	children.push_back(new Cell(2, 2, this));

	letter = 'L';
}

OBlock::OBlock(Grid *g, int x, int y, int levelOfBirth): Block {g, x, y, levelOfBirth} {
	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(1, 3, this));

	letter = 'O';
}

SBlock::SBlock(Grid *g, int x, int y, int levelOfBirth): Block{g, x, y, levelOfBirth} {

	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(2, 2, this));
	letter = 'S';
}

TBlock::TBlock(Grid *g, int x, int y, int levelOfBirth): Block {g, x, y, levelOfBirth} {

	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 2, this));
	letter = 'T';
}

ZBlock::ZBlock(Grid *g, int x, int y, int levelOfBirth): Block {g, x, y, levelOfBirth} {

	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	letter = 'Z';
}


char OBlock::getLetter() {
    return 'O';  // The letter 'O' represents the O-shaped block
}

char SBlock::getLetter() {
    return 'S';  // The letter 'S' represents the S-shaped block
}

char TBlock::getLetter() {
    return 'T';  // The letter 'T' represents the T-shaped block
}

char LBlock::getLetter() {
    return 'L';  // The letter 'L' represents the L-shaped block
}

char JBlock::getLetter() {
    return 'J';  // The letter 'J' represents the J-shaped block
}

char ZBlock::getLetter() {
    return 'Z';  // The letter 'Z' represents the Z-shaped block
}

char IBlock::getLetter() {
    return 'I';  // The letter 'I' represents the I-shaped block
}


// destructors for subclasses
OBlock::~OBlock() {}
IBlock::~IBlock() {}
LBlock::~LBlock() {}
JBlock::~JBlock() {}
SBlock::~SBlock() {}
ZBlock::~ZBlock() {}
TBlock::~TBlock() {}




// will implement later
// SingleBlock::SingleBlock(shared_ptr<Cell> child1) {}


void Block::removeCell(Cell* c){
	for (auto it = children.begin(); it != children.end();){
		if (*it == c) children.erase(it);
		else ++it;
	}
}


void Block::rotateCW(){
	int numEmptyRowsBelow = 0; // = 3 - highest 'x' amongst the cells
	
	int highestY = 0;
	for (Cell* c : children){ // I put the type here for the vector element as a reminder
		if (c->getInternalY() > highestY){
			highestY = c->getInternalY();
		}
	}
	numEmptyRowsBelow = 3 - highestY;

	// now let's do the rotation
	for (Cell *c : children){	
		c->swapCoords();
		c->reverseRows();
		c->translateInternalY(numEmptyRowsBelow);
		c->updateGridCoords();
	}
	
}
void Block::rotateCCW(){
	int numEmptyColsLeft = 3; // # of empty columns to the left, = lowest 'x' amongst the cells
	for (Cell *c :children){
		if (c->getInternalX() < numEmptyColsLeft){
			numEmptyColsLeft = c->getInternalX();
		}
	}

	// now let's do the rotation
	for (Cell *c : children){
		c->swapCoords();
		c->reverseCols();
		c->translateInternalX(-1 * numEmptyColsLeft);
		c->updateGridCoords();	
	}


}

// updates cell grid coords
void Block::updateCellCoords(){
	for (Cell *c : children){
		c->updateGridCoords();
	}
}

void Block::resetState(const std::vector<std::pair<int, int>>& originalCoords, int originalAnchorX, int originalAnchorY) {
    for (int i = 0; i< numCells(); i++) {
        children[i]->setInternalCoords(originalCoords[i].first, originalCoords[i].second);
    }
    x_anchor = originalAnchorX;
    y_anchor = originalAnchorY;
    updateCellCoords();
}

void Block::setAnchors(int newxanch, int newyanch){
	x_anchor = newxanch;
	y_anchor = newyanch;
	updateCellCoords();
}

Block::~Block(){
	// remove itself from the grid
	g->removeBlock(this);

	// if the block didn't die of old age, then it was cleared, and we increment the grid's score
	if (!blockDied){
		int scoreAdd = (levelOfBirth + 1) * (levelOfBirth + 1);
		g->addToScore(scoreAdd);
	// increment the score of the grid appropriately
	// if they've been cleared
	}

}


// sets the y_anchor to the highest 'y' value amongst the cells
void updateAnchorY(){
	for (Cell* cell : children){
		if (y_anchor < cell->getGridY()){
			y_anchor = cell->getGridY();
		}	
	}
}


vector<Cell*> Block::getCells() {
	return children;
}


// level that block was generated or "born" on
void Block::setBirthDate(int birthDate){
	levelOfBirth = birthDate;

}


// did they "die" of old age, as opposed to just being cleared
void Block::setBlockDied(bool didTheyDie){
	blockDied = didTheyDie;
}



int Block::numCells(){ return children.size(); }

void Block::incrementAge(){ lifetimeCount++; }

int Block::getAge() { return lifetimeCount; }
