
#include "level.h"

Level::Level(Grid *g): g {g}, moves {0} {}

std::shared_ptr<Block> Level::createBlock(char type, int x, int y) {
    switch(type) {
        case 'I':
            return std::make_shared<IBlock>(g);
        case 'J':
            return std::make_shared<JBlock>(g);
        case 'L':
            return std::make_shared<LBlock>(g);
        case 'O':
            return std::make_shared<OBlock>(g);
        case 'S':
            return std::make_shared<SBlock>(g);
        case 'T':
            return std::make_shared<TBlock>(g);
        case 'Z':
            return std::make_shared<ZBlock>(g);
        case '*':
            return std::make_shared<SingleBlock>(g, x, y);
    }
    return nullptr;
}

Level0::Level0(string file, Grid *g): Level(g), f {file}, filename {file} {} //be careful of closing RAII


std::shared_ptr<Block> Level0::generateBlock() {
    char nextBlock;
    if (!(f >> nextBlock)) {
        f.close();
        f.open(filename); // Reset stream

        f >> nextBlock;
    }
    return this->createBlock(nextBlock);
    
}

Level1::Level1(Grid *g): Level(g) {}


shared_ptr<Block> Level1::generateBlock() {
    char arr[12] = {'S','Z','I','I','J','J','L','L', 'O', 'O', 'T','T'};
    return this->createBlock(arr[rand() % 12]);

}

Level2::Level2(Grid *g): Level(g) {}


shared_ptr<Block> Level2::generateBlock() {
    char arr[7] = {'S','Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 7]);
}


Level3::Level3(Grid *g): Level(g) {}


shared_ptr<Block> Level3::generateBlock() {
    char arr[9] = {'S', 'S','Z', 'Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 9]);
}


Level4::Level4(Grid *g): Level(g) {}


shared_ptr<Block> Level4::generateBlock() {
    vector<pair<int, int>> emptyCoords;


    // what is this for
    /*
    if (moves != 0 && moves % 5 == 0) {
        for (int i = 3; i < 18; i++) {
            for (int j = 0; j < 15; j++) {
                if (!(g->cells[i][j])) { // Find empty spot
                    emptyCoords.emplace_back(i,j);
                }
            }
        }
    }*/
    if (g->getBlocksSinceLastClear() == 5){ // * block debuff is on, since it's level 4
        cout << "generate a * block" << endl;
        return this->createBlock('*');
    }

    int random = rand() % emptyCoords.size();

    //g->addBlock(createBlock('*', emptyCoords[random].first, emptyCoords[random].second));

    char arr[9] = {'S', 'S','Z', 'Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 9]);
}





