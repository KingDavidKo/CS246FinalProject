
#ifndef CELL_H
#define CELL_H

#include "block.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Block;
class Grid;

class Cell {
    protected:
        int x,y; // block-relative coordinates
	int grid_x, grid_y;
    Block* parent; // the Block that its a part of
				  // shared because the other 3 cells point to that Block too
	// we are going to keep this as a raw pointer until we know it works, as we don't fully undestand shared pointers yet       
       
	char letter;

    public:
        Cell(int x, int y, Block* parent);
        
	//void setParent(unique_ptr<Block> b);
	
	void swapCoords();
        void reverseRows();
        void reverseCols();
	
	void updateGridCoords(); //after changes have been made to the internal coords via rotation or translation, this gets called

	void translateInternalX(int dx);
	void translateInternalY(int dy);

	void translateGridX(int dx);
	void translateGridY(int dy);

	~Cell();
	
	void setInternalCoords(int newx, int newy);

	int getInternalX();
	int getInternalY();

	int getGridX();
	int getGridY();

	char getLetter();
	Block* getParent();
};

#endif

