#ifndef GRID_H
#define GRID_H

#include "block.h"
#include <vector>
#include <memory>
#include "cell.h"
#include "subject.h"
#include "addtext.h"
#include "addgraphics.h"
using namespace std;


class Block;
class Cell;

class Grid  : public Subject {
    
    Block* currentBlock;
    int current_x, current_y; // bottom left coords for currentBlock
	
    unique_ptr<Cell> cells[11][18]; // only Grid deletes Cells, never Block
					  // therefore unique_ptr
	// this also means that in addBlock, we get the array's vector of Cell pointers,
	// then set the index corresponding to the Cell's grid coords to the points for that cell
	//
	// so like if Block.children[2]->getGridX and getGridY are smth like 6,12, then
	// cells[6][12] = make_unique(*Block.children[2])
        
	//vector<vector<shared_ptr<Cell>>> cells;
	// 2D array, not a vector, as the board is a set size


    vector<Block*> blocksInGrid; // In order of generation
				      // raw pointer because Cell will delete Block,
				      // so Grid doesn't need to
				      // the grid dtor should destruct every cell in thegrid to ensure that this happens
        
    int score;
    int level;
	

    bool blind, heavy; // don't think we need a bool for the force debuff
    bool gameOver;


    // add int blocksSinceLastDrop, bool level3, bool level4 later
    
    void clearFullRows();
    
    public:
	//int rows, columns;
        Grid();
        void addBlock(Block block); // adds block to top left, updating the grid coords for that block and the cells in that block
        void removeBlock(Block *b); // used only when all block cells are cleared
	// raw pointer cause it uses "this" in the block's method	


	void dropBlock();
        bool isGameOver();
        vector<char> returnState(int n); // returns a row of chars representing the grid
	
	void setCurrent(Block& b); // set current block
		

	bool isValidMove(Block* b, int dx, int dy, bool CW, bool CCW);
    	void moveBlock(Block* b, int dx, int dy, bool CW, bool CCW);
	void dropBlock(Block* b);


	// accessors and mutators
	int getLevel();
	int getScore();
	Block* returnCurrentBlock(); 
	void setCurrentBlock(Block* freshBlock);
	void addToScore(int s);
	void setLevel(int newlevel);

	void setBlind(bool isBlind);
	void setHeavy(bool isHeavy);

	~Grid();
};

#endif
