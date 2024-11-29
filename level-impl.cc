
#include "level.h"

Level::Level(Grid*  g): g {g}, moves {0} {}

std::shared_ptr<Block> Level::createBlock(char type, int level) {
    switch(type) {
        case 'I':
            return std::make_shared<IBlock>(g, 0, 3, level);
        case 'J':
            return std::make_shared<JBlock>(g, 0, 3, level);
        case 'L':
            return std::make_shared<LBlock>(g, 0, 3, level);
        case 'O':
            return std::make_shared<OBlock>(g, 0, 3, level);
        case 'S':
            return std::make_shared<SBlock>(g, 0, 3, level);
        case 'T':
            return std::make_shared<TBlock>(g, 0, 3, level);
        case 'Z':
            return std::make_shared<ZBlock>(g, 0, 3, level);
        case '*':
            return std::make_shared<SingleBlock>(g, 5, 3); // level doesn't matter for this, as clearin * doesn't add to the score anyways
    }
    return nullptr;
}

Level0::Level0(string file, Grid* g): Level(g), f {file}, filename {file} {} //be careful of closing RAII


std::shared_ptr<Block> Level0::generateBlock() {
    char nextBlock;
    if (!(f >> nextBlock)) {
        f.close();
        f.open(filename); // Reset stream

        f >> nextBlock;
    }
    return this->createBlock(nextBlock, 0);
    
}

Level1::Level1(Grid* g): Level(g) {}


shared_ptr<Block> Level1::generateBlock() {
    char arr[12] = {'S','Z','I','I','J','J','L','L', 'O', 'O', 'T','T'};
    return this->createBlock(arr[rand() % 12], 1);

}

Level2::Level2(Grid* g): Level(g) {}


shared_ptr<Block> Level2::generateBlock() {
    char arr[7] = {'S','Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 7], 2);
}


Level3::Level3(Grid* g): Level(g) {}


shared_ptr<Block> Level3::generateBlock() {
    char arr[9] = {'S', 'S','Z', 'Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 9], 3);
}


Level4::Level4(Grid* g): Level(g) {}


shared_ptr<Block> Level4::generateBlock() {
    if (g->getBlocksSinceLastClear() % 5 == 0 && g->getBlocksSinceLastClear() != 0){ // * block debuff is on, since it's level 4
        cout << "generate a * block" << endl;
        g->dropBlock(createBlock('*', 4));
    }


    char arr[9] = {'S', 'S','Z', 'Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 9], 4);
}





