#include "gameController.h"
#include "player.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

gameController::gameController(int level, bool textOnly, int seed, string file1, string file2): playerOne {Player(level)}, playerTwo {Player(level)} {
    // Arguments
    level = level;
    textOnly = textOnly;
    file1 = file1;
    file2 = file2;
    currentPlayer = &playerOne;
    fileInput = false;
    
    if (seed >= 0) {
        srand(seed);
    }

    // Commands
    command["left"] = "left";
    command["right"] = "right";
    command["down"] = "down";
    command["clockwise"] = "clockwise";
    command["counterclockwise"] = "counterclockwise";
    command["drop"] = "drop";
    command["levelup"] = "levelup";
    command["leveldown"] = "leveldown";
    command["norandom"] = "norandom"; // the next word we take in will be a filename
    command["random"] = "random";
    command["sequence"] = "sequence";
    command["I"] = "I";
    command["J"] = "J";
    command["L"] = "L";
    command["O"] = "O";
    command["S"] = "S";
    command["Z"] = "Z";
    command["T"] = "T";
    command["restart"] = "restart";
    command["blind"] = "blind";
    command["heavy"] = "heavy";
    command["force"] = "force";
    command["rename"] = "rename";

}

void gameController::run() {
    
    string command;
    //currentPLayer = 1;
    
    
    
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

string gameController::decipherCommand(string toInterpret) {
    istringstream input{toInterpret};

    int multiplier = -1;
    if (!(input >> multiplier)) {
        input.clear();
    }


    string potentialCommand;
    input >> potentialCommand;
    string result = commandMatch(potentialCommand);
    // maybe return result right here
    if (result == "restart" || result == "ambiguous" || result == "invalid" || result == "sequence") {
        return result; // wait if we restart the game all keybinds would be gone? 
        // ok lowk this has to be in main. we have to open a file if we're in sequence. cannot handle it here
    }
    // else if (result == "hint") {

    // }
    else if (result == "norandom" || result == "random") {
        if (currPlayer->level < 3) {
            break;
        }
        if (result == "norandom") {
            string seqFile;
            cin >> seqFile; // dont know if we're reading from a file...
        }
        else {
            seqFile = "";
        }
        currPlayer->level->setFile(seqFile);
        
        // pass level seqFile. level knows that if seqFile isn't an empty string then it has to use norandom from now on. otherwise it resets
    }
    else if (isABlock(result)) {
        currPlayer->currBlock = Block(result); // have to make sure that copy assignment of blocks deletes the old one or smth that works with unique pointers
    }
    else if (result == "blind") {
        opponent=>grid->blind;
    }
    else if (result == "heavy") {
        // apply heavy modifier here
    }
    else if (result == "force") {
        string block;
        cin >> block;
        if (isABlock(block)) {
            opponent->currBlock(block);
            if (opponent->lost()) {
                return "WON";
            }
        }
    }
    else {
        matchMultiplied(result, multiplier); // handles all multiplied stuff
        return ""; // placeholder ig, when we move it all to main it should be fine
    }
}

string gameController::commandMatch(const string &input) {
    string matchedCommand;
    int matchCount = 0;

    for (auto &command : this->command) {
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
        return "ambiguous"; // Too many matches
    } else {
        return "invalid"; // No match
    }
}