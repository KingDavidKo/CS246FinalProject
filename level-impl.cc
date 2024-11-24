
#include "level.h"

Level::Level(Grid *g): g {g}, moves {0} {}

Block Level::createBlock(char type, int x, int y) {
    switch(type) {
        case 'I':
            return IBlock(g);
        case 'J':
            return JBlock(g);
        case 'L':
            return LBlock(g);
        case 'O':
            return OBlock(g);
        case 'S':
            return SBlock(g);
        case 'T':
            return TBlock(g);
        case 'Z':
            return ZBlock(g);
        case '*':
            return SingleBlock(g, x, y);
    }
}

Level0::Level0(string file, Grid *g): Level(g), f {file}, filename {file} {} //be careful of closing RAII


Block Level0::generateBlock() {
    char nextBlock;
    if (!(f >> nextBlock)) {
        f.close();
        f.open(filename); // Reset stream

        f >> nextBlock;
    }
    return this->createBlock(nextBlock);
    
}

Level1::Level1(Grid *g): Level(g) {}


Block Level1::generateBlock() {
    char arr[12] = {'S','Z','I','I','J','J','L','L', 'O', 'O', 'T','T'};
    return this->createBlock(arr[rand() % 12]);

}

Level2::Level2(Grid *g): Level(g) {}


Block Level2::generateBlock() {
    char arr[7] = {'S','Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 7]);
}


Level3::Level3(Grid *g): Level(g) {}


Block Level3::generateBlock() {
    char arr[9] = {'S', 'S','Z', 'Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 9]);
}


Level4::Level4(Grid *g): Level(g) {}


Block Level4::generateBlock() {
    vector<pair<int, int>> emptyCoords;

    if (moves != 0 && moves % 5 == 0) {
        for (int i = 3; i < g->rows; i++) {
            for (int j = 0; j < g->columns; j++) {
                if (!(g->cells[i][j])) { // Find empty spot
                    emptyCoords.emplace_back(i,j);
                }
            }
        }
    }
    int random = rand() % emptyCoords.size();

    g->addBlock(createBlock('*', emptyCoords[random].first, emptyCoords[random].second));

    char arr[9] = {'S', 'S','Z', 'Z','I','J','L','O','T'};
    return this->createBlock(arr[rand() % 9]);
}





