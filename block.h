#include <string>
#include <vector>
#include "cell.h"
#include "grid.h"
#include <memory.h>
using namespace std;

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


    public:
        Block(int x, int y, Grid *g); // Set anchor point
			     // don't need defaults as this should never be called
        void move(string dir);
        void rotateCW();
        void CCW();
	~Block(); // this can be implemented, idk what method to make virtual for this abtract class
	
	void removeCell(Cell &c);	
	// accessors and mutators
	int getXAnchor();
	int getYAnchor();
	int numCells(); // size of children Cell vector
			// if 0, this Block should be deleted
	vector<Cell*> getCells(); // get the  cells from this Block (useful for Grid)
	void setXAnchor(int x);
	void setYAnchor(int y);
	
	char getLetter();

};

// for the subclasses, the Block ctors cell pointer arguments may not be needed as the Block will make the cells according to whichever block they are (so J blocks will initialize their cells in a certain way and stuff)


// default y is 3 cause the default grid anchor is just the internal coords
class IBlock : public Block {
    public:
        IBlock(int x = 0, int y = 3, Grid *g);    
};

class JBlock : public Block {
    public:
        JBlock(int x = 0, int y =  3, Grid *g);    
};

class LBlock : public Block {
    public:
        LBlock(int x = 0, int y = 3, Grid *g);    
};

class OBlock : public Block {
    public:
        OBlock(int x = 0, int y = 3, Grid *g);    
};

class SBlock : public Block {
    public:
        SBlock(int x = 0, int y = 3, Grid *g);    
};

class TBlock : public Block {
    public:
        TBlock(int x = 0, int y = 3, Grid *g);    
};

class ZBlock : public Block {
    public:
        ZBlock(int x = 0, int y = 3, Grid *g);    
};


// not sure what this is for
// maybe the one debuff?
class SingleBlock : public Block {
    public:
        SingleBlock(int x, int y);    
};

