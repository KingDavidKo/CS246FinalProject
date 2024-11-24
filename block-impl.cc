#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>
#include "cell.h"
#include "grid.h"
#include "block.h"
#include <memory.h>
using namespace std;


Block::Block(Grid *g, int x, int y): x_anchor {x}, y_anchor {y}, g {g} {
	lifetimeCount = 0;
	// rest of fields don't need to be added cause Block should be abstract	
}

IBlock::IBlock(Grid *g, int x, int y): Block{g, x, y} {
	// inititalize the children cell vector
	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	children.push_back(new Cell(3, 3, this));


	// add the letter
	letter= 'I';
}



JBlock::JBlock(Grid *g, int x, int y): Block{g, x, y} {

	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	
	letter = 'J';
}

LBlock::LBlock(Grid *g, int x, int y): Block{g, x, y} {

	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	children.push_back(new Cell(2, 2, this));

	letter = 'L';
}

OBlock::OBlock(Grid *g, int x, int y): Block {g, x, y} {
	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(1, 3, this));

	letter = 'O';
}

SBlock::SBlock(Grid *g, int x, int y): Block{g, x, y} {

	children.push_back(new Cell(0, 3, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(2, 2, this));
	letter = 'S';
}

TBlock::TBlock(Grid *g, int x, int y): Block {g, x, y} {

	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 2, this));
	letter = 'T';
}

ZBlock::ZBlock(Grid *g, int x, int y): Block {g, x, y} {

	children.push_back(new Cell(0, 2, this));
	children.push_back(new Cell(1, 2, this));
	children.push_back(new Cell(1, 3, this));
	children.push_back(new Cell(2, 3, this));
	letter = 'Z';
}

// will implement later
// SingleBlock::SingleBlock(shared_ptr<Cell> child1) {}



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

#endif
