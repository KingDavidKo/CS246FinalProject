#include <string>
#include <vector>
#include "cell.h"
#include <memory.h>
using namespace std;

class Block {
    protected:
        int x,y;
        vector<shared_ptr<Cell>> children;

    public:
        Block(int x = 0, int y = 0); // Set anchor point
        void move(string dir);
        void rotateCW();
        void CCW();
};

class IBlock : public Block {
    public:
        IBlock(shared_ptr<Cell> child1, shared_ptr<Cell> child2, shared_ptr<Cell>, shared_ptr<Cell> child3, shared_ptr<Cell> child4);    
};

class JBlock : public Block {
    public:
        JBlock(shared_ptr<Cell> child1, shared_ptr<Cell> child2, shared_ptr<Cell>, shared_ptr<Cell> child3, shared_ptr<Cell> child4);    
};

class LBlock : public Block {
    public:
        LBlock(shared_ptr<Cell> child1, shared_ptr<Cell> child2, shared_ptr<Cell>, shared_ptr<Cell> child3, shared_ptr<Cell> child4);    
};

class OBlock : public Block {
    public:
        OBlock(shared_ptr<Cell> child1, shared_ptr<Cell> child2, shared_ptr<Cell>, shared_ptr<Cell> child3, shared_ptr<Cell> child4);    
};

class SBlock : public Block {
    public:
        SBlock(shared_ptr<Cell> child1, shared_ptr<Cell> child2, shared_ptr<Cell>, shared_ptr<Cell> child3, shared_ptr<Cell> child4);    
};

class TBlock : public Block {
    public:
        TBlock(shared_ptr<Cell> child1, shared_ptr<Cell> child2, shared_ptr<Cell>, shared_ptr<Cell> child3, shared_ptr<Cell> child4);    
};

class ZBlock : public Block {
    public:
        ZBlock(shared_ptr<Cell> child1, shared_ptr<Cell> child2, shared_ptr<Cell>, shared_ptr<Cell> child3, shared_ptr<Cell> child4);    
};

class SingleBlock : public Block {
    public:
        SingleBlock(shared_ptr<Cell> child1);    
};

