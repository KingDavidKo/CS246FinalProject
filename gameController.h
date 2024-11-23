#include "player.h"
#include <map>
#include <string>
using namespace std;

class gameController {
    protected:
        Player playerOne;
        Player playerTwo;
        int level;
        map <string, string> decipherCommand;

    public:
        gameController();
        void renameCommand(string og, string curr);
        void start();
};
