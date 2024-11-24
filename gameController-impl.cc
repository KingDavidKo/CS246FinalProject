#include "gameController.h"
#include "player.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

gameController::gameController(int level, bool textOnly, int seed, string file1, string file2) {

    

    // Arguments
    level = level;
    textOnly = textOnly;
    file1 = file1;
    file2 = file2;
    playerOne = Player(level);
    playerTwo = Player(level);
    
    if (seed >= 0) {
        srand(seed);
    }

    // Commands
    decipherCommand["left"] = "left";
    decipherCommand["right"] = "right";
    decipherCommand["down"] = "down";
    decipherCommand["clockwise"] = "clockwise";
    decipherCommand["counterclockwise"] = "counterclockwise";
    decipherCommand["drop"] = "drop";
    decipherCommand["levelup"] = "levelup";
    decipherCommand["leveldown"] = "leveldown";
    decipherCommand["norandom file"] = "norandom file";
    decipherCommand["random"] = "random";
    decipherCommand["sequence file"] = "sequence file";
    decipherCommand["I"] = "I";
    decipherCommand["J"] = "J";
    decipherCommand["L"] = "L";
    decipherCommand["O"] = "O";
    decipherCommand["S"] = "S";
    decipherCommand["Z"] = "Z";
    decipherCommand["T"] = "T";
    decipherCommand["restart"] = "T";
    decipherCommand["blind"] = "blind";
    decipherCommand["heavy"] = "heavy";
    decipherCommand["force"] = "force";

}

void gameController::run() {
    
    string command;

    /*
    
    Potential problem for when renaming commands in map, keys are not able to be renamed


    */

    // while ( cin >> command ) {
        

    //     switch(c) {
    //       case 'n':
    //         // Create new IntSet at index lhs after destroying the old.
    //         // Read in integers to add to it until hitting non-int using operator>>.
    //         cin >> lhs;
    //         delete sets[lhs];
    //         sets[lhs] = new IntSet;
    //         cin >> *sets[lhs];
    //         break;
}

string gameController::commandMatch(const string &input) {
    string matchedCommand;
    int matchCount = 0;

    for (auto &command : this->decipherCommand) {
        if (input.length() > command.first.length()) {
            continue;
        }
        for (int i = 0; i < input.length(); i++) {
            if (command.first[i] != input[i]) {
                continue;
            }
        }
        matchedCommand = command.second;
        matchCount++;
    } 

    if (matchCount == 1) {
        return matchedCommand; // Unique match found
    } else if (matchCount > 1) {
        return "AMBIGUOUS"; // Too many matches
    } else {
        return "INVALID"; // No match
    }
}