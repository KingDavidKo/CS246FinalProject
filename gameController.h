#include "player.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class gameController {

    string commandMatch(const string &input);
    protected:
        Player playerOne;
        Player playerTwo;
        int level;
        map <string, string> command;
        bool textOnly;
        int seed;
        string file1;
        string file2;
        Player * currentPlayer;
        bool fileInput;


    public:
        gameController(int level = 0, bool textOnly = false, int seed = -1, string file1 = "sequence1.txt", string file2 = "sequence2.txt");
        string decipherCommand(string toInterpret);
        void renameCommand(string og, string curr);
        void run();
};
