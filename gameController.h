#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "player.h"
#include "window.h"
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

class gameController {

    string commandMatch(const string &input);
    void matchMultiplied(string result, int multiplier);
    string fileParse(string fileName);
    void multipleCommmandHandler(string result);
    vector<string>blocks;

    protected:
        Player playerOne;
        Player playerTwo;
        int level;
        map <string, string> command;
        bool textOnly;
        int seed;
        string file1;
        string file2;
        Player* currentPlayer;
        Player* opponent;
        Xwindow* window;
    public:
        gameController(int level = 0, bool textOnly = false, int seed = -1, string file1 = "sequence1.txt", string file2 = "sequence2.txt");
        string decipherCommand(string toInterpret, bool readingFromFile = false);
        void renameCommand(string og, string curr);
        void run();
        void render();
        bool isABlock(string potentialBlock);
};

#endif
