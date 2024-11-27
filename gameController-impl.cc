#include "gameController.h"
using namespace std;

gameController::gameController(int level, bool textOnly, int seed, string file1, string file2): playerOne {Player(level)}, playerTwo {Player(level)} {
    // Arguments
    level = level;
    textOnly = textOnly;
    file1 = file1;
    file2 = file2;
    currentPlayer = &playerOne;
    opponent = &playerTwo;
    vector<string> blocks = {"I", "J", "L", "O", "S", "Z", "T"};
    this->blocks = blocks;

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
    // initialize all the stuff!
    string command;
    while (cin >> command) {
        string result = decipherCommand(command);
        if (result == "restart") {
            // destroy the boards and remake them!
            // keeps the keybinds intact this way
        }
        else if (result == "ambiguous" || result == "invalid") {
            cout << result << endl;
        }
    }
  

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

bool gameController::isABlock(string potentialBlock) {
    bool isInVecOfValidBlocks = std::find(blocks.begin(), blocks.end(), potentialBlock) != blocks.end();
    return isInVecOfValidBlocks;
}


void gameController::matchMultiplied(string result, int multiplier) {
    if (multiplier == -1) {
        multipleCommmandHandler(result);
    }
    else {
        for (int i = multiplier; i > 0; i--) {
            multipleCommmandHandler(result);
        }
    }
    // now notify
}

void gameController::multipleCommmandHandler(string result) {
    if (result == "left") {
        // apply left
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), -1, 0, false, false)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), -1, 0, false, false);
        }
    }
    else if (result == "right") {
        // apply right
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 1, 0, false, false)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 1, 0, false, false);
        }
    }
    else if (result == "down") {
        // apply down
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 1, false, false)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 1, false, false);
        }
    }
    else if (result == "clockwise") {
        // apply clockwise
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 0, true, false)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 0, true, false);
        }
    }
    else if (result =="counterclockwise") {
        // apply counterclockwise
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 0, false, true)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 0, false, true);
        }
    }
    else if (result == "drop") {
        // apply drop logic. should be done in a way such that i can continuously call drop a ton of times and nothing happens
        currentPlayer->grid->dropBlock();
        Player * temp = currentPlayer;
        currentPlayer = opponent;
        opponent = temp;
    }
    else if (result == "levelup") {
        // apply levelup
        currentPlayer->incrementLevel();
    }
    else if (result == "leveldown") {
        // apply leveldown  
        currentPlayer->decrementLevel();
    }
    else {
        cout << "invalid command, try again!" << endl;
    }
    // check if we need to switch to the other player regardless? or we could just force player to drop
    render();
}


void gameController::render() {
    cout << "Level:\t" << playerOne.returnLevel() << "\t" << "Level:\t" << playerTwo.returnLevel() << endl;
    cout << "Score:\t" << playerOne.score << "\t" << "Score:\t" << playerTwo.score << endl;
    
    for (int i = 0; i < 18; i++) {
        playerOne.grid.get()->notifyObservers(i);
        cout << "\t";
        playerTwo.grid.get()->notifyObservers(i);
        cout << endl;
    }
    cout << "-----------\t-----------" << endl;
    cout << "Next:      \tNext:      " << endl;

    ///////
    // Print next block here
    ///////

    if (!textOnly) {
        ///////
        // Do graphical here
        ///////
        return;
    }
}

string gameController::fileParse(string fileName) {
    ifstream in {fileName};
    string s;
    while (in >> s) {
        string result;
        result = decipherCommand(s, true);
        if (result == "") {
            continue;
        }
        else if (result == "ambiguous" || result == "invalid") {
            cout << result << endl;
        }
        else if (result == "return") {
            return result;
        }
        else if (result == "sequence") {
            string temp;
            in >> temp;
            temp = fileParse(temp);
            if (temp != "") {
                return temp; // only thing that should be returning should really just be "restart"
            }
        }
        else if (result == "norandom") { // norandom
            string seqFile;
            in >> seqFile;
            currentPlayer->level->setFile(seqFile); // set File does not exist at this moment!
        }
        else if (result == "force") {
            string block;
            in >> block;
            if (isABlock(block)) { // reprompt maybe if it's not  a block
                opponent->setCurrentBlock(block); 
                if (opponent->lost()) {
                    return "WON";
                }
            }
        }
        else {
            cerr << "FileParse error" << endl; // we should never get to this stage?
        }
    }
    return "";
} 

string gameController::decipherCommand(string toInterpret, bool readingFromFile) { // also maybe need a bool for special action triggers
    istringstream input{toInterpret};
    int multiplier = -1;
    if (!(input >> multiplier)) {
        input.clear();
        multiplier = -1;
    }

    string potentialCommand;
    input >> potentialCommand;
    string result = commandMatch(potentialCommand);
    // maybe return result right here
    if (result == "restart" || result == "ambiguous" || result == "invalid")  {
        return result; // wait if we restart the game all keybinds would be gone? 
    }
    // else if (result == "hint") {

    // }
    else if (result == "sequence") {
        if (readingFromFile) {
            return result;
        }
        else {
            string fileName;
            cin >> fileName;
            return fileParse(fileName); // basically allows errors to propogate backwards
        }
    }

    else if (result == "norandom" || result == "random") {
        string seqFile;
        if (currentPlayer->returnLevel() < 3) {
            return ""; // no need to do anything
        }
        if (result == "norandom") {
            if (!readingFromFile) {
                cin >> seqFile;
            }
            else {
                return result; // let caller deal with it
            }
        }
        else {
            seqFile = ""; // result was random, so seqFile should be nothing!
        }
        currentPlayer->level->setFile(seqFile); // i can't change the file from here...
        
        // pass level seqFile. level knows that if seqFile isn't an empty string then it has to use norandom from now on. otherwise it resets
    }
    else if (isABlock(result)) {
        currentPlayer->grid->setCurrentBlock(Block()); // have to make sure that copy assignment of blocks deletes the old one or smth that works with unique pointers
    }
    else if (result == "blind") {
        opponent->grid->blind();
    }
    else if (result == "heavy") {
        // apply heavy modifier here
    }
    else if (result == "force") {
        if (readingFromFile) {
            return result;
        }
        else {
            string block;
            cin >> block;
            if (isABlock(block)) { // reprompt maybe if it's not  a block
                opponent->setCurrentBlock(block); 
                if (opponent->lost()) {
                    return "WON";
                }
            }
        }
    }
    else {
        matchMultiplied(result, multiplier); // handles all multiplied stuff
    }
    return ""; 
}

string gameController::commandMatch(const string &input) {
  string matchedCommand;
  int matchCount = 0;
  bool isAMatch = true;

  for (auto &command : this->command) {
    if (input.length() > command.first.length()) {
      continue;
    }
    for (int i = 0; i < input.length(); i++) {
      if (command.first[i] != input[i]) {
        isAMatch = false;
        break;
      }
    }
    if (isAMatch) {
      matchedCommand = command.second;
      matchCount++;
    }
    isAMatch = true;
  }

  if (matchCount == 1) {
    return matchedCommand; // Unique match found
  } else if (matchCount > 1) {
    return "ambiguous"; // Too many matches
  } else {
    return "invalid"; // No match
  }
}