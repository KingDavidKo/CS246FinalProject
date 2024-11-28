#include "block.h"
#include "grid.h"
#include <cstdlib>
#include <fstream>
#include <string>

class Level {
    protected:
        Grid *g;
        int moves;
    public:
        Level(Grid *g);
        virtual std::shared_ptr<Block> generateBlock() = 0;
        std::shared_ptr<Block> createBlock(char type, int x = 0, int y = 3);
};


class Level0 : public Level {
    private:
        ifstream f; // Maintain state
        string filename;
    public:
        Level0(string file, Grid *g);
        std::shared_ptr<Block> generateBlock();
};

class Level1 : public Level {
    public:
        Level1(Grid *g);
        std::shared_ptr<Block> generateBlock();
};

class Level2 : public Level {
    public:
        Level2(Grid *g);
        std::shared_ptr<Block> generateBlock();

};

class Level3 : public Level {
    public:
        Level3(Grid *g);
        std::shared_ptr<Block> generateBlock();
};

class Level4 : public Level {
    public:
        Level4(Grid *g);
        std::shared_ptr<Block> generateBlock();
};
