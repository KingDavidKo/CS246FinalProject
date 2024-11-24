#ifndef CELL_H
#define CELL_H

#include "block.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

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
	
       	void updateGridCoords(); // gets the grid coords from parent and adjusts its own x_grid and y_grid accordingly
	void swapCoords();
        void reverseRows();
        void reverseCols();
	
	void updateGridCoords(); //after changes have been made to the internal coords via rotation, this gets called

	void translateInternalX(int dx);
	void translateInternalY(int dy);

	void translateGridX(int dx);
	void translateGridY(int dy);

	~Cell();

	int getInternalX();
	int getInternalY();

	int getGridX();
	int getGridY();

};

#endif
