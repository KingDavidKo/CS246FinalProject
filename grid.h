#include "block.h"
#include <vector>
#include "cell.h"
using namespace std;

class Grid {
    protected:
        Block currentBlock;
        vector<vector<shared_ptr<Cell>>> cells;
        vector<Block<shared_ptr<Cell>>> blocksInGrid;
      


    public:
        Grid();
        void addBlock(Block& block);
        
};
