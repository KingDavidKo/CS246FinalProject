#ifndef BLOCK_H
#define BLOCK_H


#include <string>
#include <vector>
#include "cell.h"
#include "grid.h"
#include <memory>
#include <utility>

using namespace std;

class Cell;
class Grid;

class Block {
    protected: // block doesn't have children so maybe just make private
        
	//int x,y; // these grid-independent coords may or may not make sense to have
        // the coords are represented as the cells anyways

	vector<Cell*> children; // just a vector of cell pointers, as only the Grid ever needs to free Cell objects
	
	Grid *g; // pointer to that grid
		 // raw pointer as Block isn't freeing grid
		 // need the pointer to update grid score + remove it from grid vector of blocks if needed
	int lifetimeCount; // "age" of block
	int x_anchor, y_anchor; // anchor coords on Grid (bottom left 'box')
	char letter;

	int levelOfBirth; // level in which it was born
	bool blockDied;

    public:
        Block(Grid *g, int x = 0, int y = 0, int levelOfBirth = 0); // Set anchor point
			     // don't need defaults as this should never be called
                 // I want to as an empty block for grid's currentBlock (default constructor)
        void move(string dir);
        void rotateCW();
        void rotateCCW();
	virtual ~Block(); // this can be implemented, idk what method to make virtual for this abtract class
	
	void resetState(const std::vector<std::pair<int, int>>& originalCoords, int originalAnchorX, int originalAnchorY);

	void removeCell(Cell* c);	
	// accessors and mutators
	int getXAnchor();
	int getYAnchor();
	int numCells(); // size of children Cell vector
			// if 0, this Block should be deleted
	
	
	vector<Cell*> getCells(); // get the  cells from this Block (useful for Grid)
	void setXAnchor(int x);
	void setYAnchor(int y);
	void setAnchors(int newxanch, int newyanch);

	void setBirthDate(int birthDate);

	void setBlockDied(bool didTheyDie);
	// update cell grid coords	
	void updateCellCoords();	
	
	
	virtual char getLetter() = 0; // this is what makes Block an abstract class


};

// for the subclasses, the Block ctors cell pointer arguments may not be needed as the Block will make the cells according to whichever block they are (so J blocks will initialize their cells in a certain way and stuff)


// default y is 3 cause the default grid anchor is just the internal coords
class IBlock : public Block {
    public:
        IBlock(Grid *g, int x = 0, int y = 3, int levelOfBirth = 0);
	char getLetter() override;    	
	~IBlock();
};

class JBlock : public Block {
    public:
        JBlock(Grid *g, int x = 0, int y = 3, int levelOfBirth = 0);   
	char getLetter() override;
	~JBlock();
};

class LBlock : public Block {
    public:
        LBlock(Grid *g, int x = 0, int y = 3, int levelOfBirth = 0);
	char getLetter() override;
	~LBlock();
};

class OBlock : public Block {
    public:
        OBlock(Grid *g, int x = 0, int y = 3, int levelOfBirth = 0);    
	char getLetter() override;
	~OBlock();
};

class SBlock : public Block {
    public:
        SBlock(Grid *g, int x = 0, int y = 3, int levelOfBirth = 0);    
	char getLetter() override;
	~SBlock();
};

class TBlock : public Block {
    public:
        TBlock(Grid *g, int x = 0, int y = 3, int levelOfBirth = 0);    
	char getLetter() override;
	~TBlock();
};

class ZBlock : public Block {
    public:
        ZBlock(Grid *g, int x = 0, int y = 3, int levelOfBirth = 0);    
	char getLetter() override;
	~ZBlock();
};


// not sure what this is for
// maybe the one debuff?
class SingleBlock : public Block {
    public:
        SingleBlock(Grid *g, int x, int y);    
};

#endif
