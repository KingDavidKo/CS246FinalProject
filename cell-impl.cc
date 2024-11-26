#include "block.h"
#include "cell.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;


// note: each Cell should have their own shared_ptr
Cell::Cell(int x, int y, Block* parent): x {x}, y {y}, parent {parent} {
	letter = parent->getLetter();
	grid_x = x; // default
	grid_y = y; // default
	// the default grid coords is just the internal ones cause the starting placement of a Block on a Grid is a 4x4 box in the top left
	// with the Block in the bottom left of that box (that's why there is 3 reserve rows)
}


void Cell::swapCoords(){
	int temp = y;
	y = x;
	x = temp;
}

void Cell::reverseRows(){
	x = 3-x;
}

void Cell::reverseCols(){
	y = 3-x;
}

Cell::~Cell(){
	parent->removeCell(this);
	
	if (parent->numCells() == 0) delete parent;
	// if the parent Block has no more cells (like all have been cleared), then it should be deleted
	// otherwise, the parent Block should not be deleted
}


void Cell::translateInternalX(int dx){
	x += dx;
}

void Cell::translateInternalY(int dy){
	y += dy;
}

void Cell::translateGridX(int dx){
	grid_x += dx;
}

void Cell::translateGridY(int dy){
	grid_y += dy;
}


// sets grid coords to translated internal coords, taking the anchor into account
void Cell::updateGridCoords(){
	grid_x = parent->getXAnchor() + x;
	grid_y = parent->getYAnchor() - 3 + y;
}


void Cell::setInternalCoords(int newx, int newy){
	x = newx;
	y = newy;
}


int Cell::getInternalX(){
	return x;
}

int Cell::getInternalY(){
	return y;
}

int Cell::getGridX(){
	return grid_x;
}

int Cell::getGridY(){
	return grid_y;
}

char Cell::getLetter(){
	return letter;
}

