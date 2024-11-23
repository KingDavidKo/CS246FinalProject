#include "block.h"

class Level {
    
    public:
        virtual Level();
        virtual Block createBlock() = 0;
        
};


class Level0 : public Level {
    public:
        Block createBlock() = 0;
}

class Level1 : public Level {
    public:
        Block createBlock() = 0;

}

class Level2 : public Level {
    public:
        Block createBlock() = 0;

}

class Level3 : public Level {
    public:
        Block createBlock() = 0;

}

class Level4 : public Level {
    public:
        Block createBlock() = 0;

}