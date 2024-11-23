#include "block.h"
#include <vector>
#include "cell.h"
using namespace std;

class Grid {
    protected:
        Block currentBlock;
        vector<vector<shared_ptr<Cell>>> cells;
        vector<shared_ptr<Block>> blocksInGrid; // In order of generation
        int rows, columns;

    public:
        Grid();
        void addBlock(Block& block);
        void dropBlock();
        bool isGameOver();
        bool returnState();
};
