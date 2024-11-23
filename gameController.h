#include "player.h"
#include <map>
#include <string>
using namespace std;

class gameController {

    string commandMatch(const string &input);
    protected:
        Player playerOne;
        Player playerTwo;
        int level;
        map <string, string> decipherCommand;
        bool textOnly;
        int seed;
        string file1;
        string file2;


    public:
        gameController(int level = 0, bool textOnly = false, int seed = -1, string file1 = "sequence1.txt", string file2 = "sequence2.txt");
        void renameCommand(string og, string curr);
        void run();
};
