#include "gameController.h"
using namespace std;

const int PIXEL_SIZE = 10;
const int GRAPHIC_ROW_SIZE = 25;
const int GRAPHIC_COL_SIZE = 11;

gameController::gameController(int level, bool textOnly, int seed, string file1, string file2): playerOne {Player(1, level, file1)}, playerTwo {Player(2, level, file2)} {
    // Arguments
    this->level = level;
    this->textOnly = textOnly;
    this->file1 = file1;
    this->file2 = file2;
    currentPlayer = &playerOne;
    opponent = &playerTwo;
    vector<string> blocks = {"I", "J", "L", "O", "S", "Z", "T"};
    this->blocks = blocks;
    if (!textOnly){
        this->window = new Xwindow(2*GRAPHIC_COL_SIZE*PIXEL_SIZE + 10, GRAPHIC_ROW_SIZE*PIXEL_SIZE);
    }
    else{
        this->window = nullptr;
    }
     

    if (seed >= 0) {
        srand(seed);
    } else {
        srand(time(NULL));
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
    render();
    while (cin >> command) {
        
        if (currentPlayer->grid->isGameOver()) {
            return;
        }
        string result = decipherCommand(command);
        if (result == "restart") {
            // destroy the boards and remake them!
            // keeps the keybinds intact this way
        }
        else if (result == "ambiguous" || result == "invalid") {
            cout << result << endl;
        }
        render();
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

void gameController::levelHeavy(){

    // if it's a '*', then heavy doesn't apply
    if (currentPlayer->grid->isLevelHeavy()){
        // if we can move it down 1, we move it down 1
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 1, 0, 0)){
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 1, 0, 0);
        } 
    }
}

void gameController::specialHeavy(){
// heavy special action check

    // if it's a '*', then heavy doesn't apply
    if (currentPlayer->grid->isHeavy()){
                
        // if we can move it down two rows
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 2, 0, 0)){
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 2, false, false);
                
        }
        else{ // otherwise, we drop it
            multipleCommmandHandler("drop");
        }
    }
    

}

void gameController::multipleCommmandHandler(string result) {
    if (result == "left") {
        // apply left
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), -1, 0, false, false)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), -1, 0, false, false);
 
        }
        // level heavy check and application
        levelHeavy();

        // special heavy check and application
        specialHeavy();
    }
    else if (result == "right") {
        // apply right
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 1, 0, false, false)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 1, 0, false, false);

            
        }
        // level heavy check and application
        levelHeavy();

        // special heavy check and application
        specialHeavy();

    }
    else if (result == "down") {
        // apply down
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 1, false, false)) {
            ///cout << "down is valid" << endl;

            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 1, false, false);
            
        }
        // level heavy check and application
        levelHeavy();
    }
    else if (result == "clockwise") {
        // apply clockwise
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 0, true, false)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 0, true, false);
        }
        // level heavy check and application
        levelHeavy();
    }
    else if (result =="counterclockwise") {
        // apply counterclockwise
        if (currentPlayer->grid->isValidMove(currentPlayer->grid->returnCurrentBlock(), 0, 0, false, true)) {
            currentPlayer->grid->moveBlock(currentPlayer->grid->returnCurrentBlock(), 0, 0, false, true);
        }// level heavy check and application
        levelHeavy();
    }
    else if (result == "drop") {
        // apply drop logic. should be done in a way such that i can continuously call drop a ton of times and nothing happens
        currentPlayer->grid->dropBlock(currentPlayer->grid->returnCurrentBlock());

        
        /*
        // if it's been 5 blocks since last clear and the centre block debuff is on?
        if (currentPlayer->grid->getBlocksSinceLastClear() == 5 && currentPlayer->grid->isCentreBlockDebuffOn()){
            cout << "debuff block time" << endl;
            // testing
            currentPlayer->incrementLevel();
            currentPlayer->incrementLevel();
            currentPlayer->incrementLevel();
            currentPlayer->incrementLevel();



            currentPlayer->grid->setCurrent(currentPlayer->playerLevel->generateBlock()); // gets a * block from generate block
            cout << "after segfault" << endl;
            currentPlayer->grid->resetBlocksSinceLastClear(); // set it back to 0, cause we add the thing every 5

            // note that the single block starts at 5th column and is dropped there
            
            //currentPlayer->grid->setCurrent(make_shared<SingleBlock>(SingleBlock(currentPlayer->grid, 5, 3, level)));


            // drop the debuff block
            cout << "current block letter: " << currentPlayer->grid->returnCurrentBlock()->getLetter() << endl;
            currentPlayer->grid->dropBlock(currentPlayer->grid->returnCurrentBlock());


        }*/


        Player * temp = currentPlayer;
        currentPlayer = opponent;
        opponent = temp;
        
        opponent->grid->setCurrent(opponent->nextBlock);
        currentPlayer->nextBlock = currentPlayer->playerLevel->generateBlock();
        
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
    
}


void gameController::render() {
    //cout << "Level:\t" << playerOne.returnLevel() << "\t" << "Level:\t" << playerTwo.returnLevel() << endl;
    
    cout << "Level:\t" << playerOne.grid->getLevel() << "\t" << "Level:\t" << playerTwo.grid->getLevel() << endl;
    cout << "Score:\t" << playerOne.grid->getScore() << "\t" << "Score:\t" << playerTwo.grid->getScore() << endl;
    
    for (int i = 0; i < 18; i++) {

        
        for (int j = 0; j < 11; j++) {


            if (i+1 >= 3 && i+1 <= 12 && j+1 >= 3 && j+1 <= 9 && playerOne.grid->isBlind()) {
                cout << '?';
                
                
            } else if(!playerOne.grid->cells[i][j]){ // blank cell
			    cout << ' ';
            }
            else{
                
                cout << playerOne.grid->cells[i][j]->getLetter();
            }
        }
        //playerOne.grid->notifyObservers(i);
        cout << "\t";
        //playerTwo.grid->notifyObservers(i);
        for (int j = 0; j < 11; j++) {


            if (i+1 >= 3 && i+1 <= 12 && j+1 >= 3 && j+1 <= 9 && playerTwo.grid->isBlind()) {
                cout << '?';    
            } else if(!playerTwo.grid->cells[i][j]){ // blank cell
			    cout << ' ';
            }
            else{
                
                cout << playerTwo.grid->cells[i][j]->getLetter();
            }
        }
        cout << endl;
    }
    cout << "-----------\t-----------" << endl;
    cout << "Next:      \tNext:      " << endl;

    //char grid[2][4] = {' '};
    char grid[2][4] =  { {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '} };
    for (auto child : currentPlayer->nextBlock->getCells()) {
            grid[child->getGridY()-2][child->getGridX()] = child->getLetter();
    }
    if (currentPlayer == &playerOne) { // we can also check playerNum here
        
        
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
            
        
    } else {
        
        for (int i = 0; i < 2; i++) {
            cout << "\t\t";
            for (int j = 0; j < 4; j++) {
                cout << grid[i][j];
            }
            cout << endl;
        }
        
    }



    ///////
    // Print next block here
    ///////
    
    if (!textOnly) {
        if (window) {
            for (int i = 0; i < 18; ++i) {
                char chr;
                for (int j = 0; j < 11; ++j) {
                    
                    if (i+1 >= 3 && i+1 <= 12 && j+1 >= 3 && j+1 <= 9 && playerOne.grid->isBlind()) {
                        chr = '?';
                        
                        
                    } else if(!playerOne.grid->cells[i][j]){ // blank cell
                        chr = ' ';
                    }
                    else{
                        chr = playerOne.grid->cells[i][j]->getLetter();
                    }
                    
                    //char chr = playerOne->getState(row, col);
                    int color = Xwindow::Black; // by default black

                    if (chr == 'S') {
                        color = Xwindow::Green; // green
                    } else if (chr == 'J') {
                        color = Xwindow::Blue;  // blue
                    } else if (chr == ' ') {
                        color = Xwindow::White; // white
                    } else if (chr == 'Z') {
                        color = Xwindow::Red;   // red
                    } else if (chr == 'I') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == 'O') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == '*') {
                        color = Xwindow::Brown;   // red
                    } 
                    else{
                        color = Xwindow::Black;   // red
                    }                      
                    window->fillRectangle(j * PIXEL_SIZE, i * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color); // update window
                }
                
                for (int j = 0; j < 11; ++j) {
                    
                    if (i+1 >= 3 && i+1 <= 12 && j+1 >= 3 && j+1 <= 9 && playerTwo.grid->isBlind()) {
                        chr = '?';
                        
                        
                    } else if(!playerTwo.grid->cells[i][j]){ // blank cell
                        chr = ' ';
                    }
                    else{
                        chr = playerTwo.grid->cells[i][j]->getLetter();
                    }

                    int color = Xwindow::Black; // by default black

                     

                    if (chr == 'S') {
                        color = Xwindow::Green; // green
                    } else if (chr == 'J') {
                        color = Xwindow::Blue;  // blue
                    } else if (chr == ' ') {
                        color = Xwindow::White; // white
                    } else if (chr == 'Z') {
                        color = Xwindow::Red;   // red
                    } else if (chr == 'I') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == 'O') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == '*') {
                        color = Xwindow::Brown;   // red
                    } 
                    else{
                        color = Xwindow::Black;   // red
                    }         
                    window->fillRectangle((GRAPHIC_COL_SIZE + j) * PIXEL_SIZE, i * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color); // update window
                }
                //window->drawString(0, 18 * PIXEL_SIZE, "-----------\t-----------"); // update window
                window->fillRectangle(0, 19 * PIXEL_SIZE, window->getWidth(), 2, Xwindow::Black);
                window->drawString(5, 20 * PIXEL_SIZE+ 2, "Next:");
                window->drawString(window->getWidth()/2 + 5, 20 * PIXEL_SIZE + 2, "Next:");
                //window->drawString(window->getWidth()/2, 20 * PIXEL_SIZE, "-----------\t-----------");
        char grid[2][4] =  { {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '} };
        for (auto child : currentPlayer->nextBlock->getCells()) {
                grid[child->getGridY()-2][child->getGridX()] = child->getLetter();
        }
    
        if (currentPlayer == &playerOne) { // we can also check playerNum here
            
                
            
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 4; j++) {
                    chr = grid[i][j];
                
                    //char chr = playerOne->getState(row, col);
                    int color = Xwindow::Black; // by default black

                     

                    if (chr == 'S') {
                        color = Xwindow::Green; // green
                    } else if (chr == 'J') {
                        color = Xwindow::Blue;  // blue
                    } else if (chr == ' ') {
                        color = Xwindow::White; // white
                    } else if (chr == 'Z') {
                        color = Xwindow::Red;   // red
                    } else if (chr == 'I') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == 'O') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == '*') {
                        color = Xwindow::Brown;   // red
                    } 
                    else{
                        color = Xwindow::Black;   // red
                    }                    
                    window->fillRectangle(j * PIXEL_SIZE, (21 +i) * PIXEL_SIZE + 2, PIXEL_SIZE, PIXEL_SIZE, color);
                }
            }
                
            
        } else {
            
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 4; j++) {
                    chr = grid[i][j];
                
                    //char chr = playerOne->getState(row, col);
                    int color = Xwindow::Black; // by default black

                     

                    if (chr == 'S') {
                        color = Xwindow::Green; // green
                    } else if (chr == 'J') {
                        color = Xwindow::Blue;  // blue
                    } else if (chr == ' ') {
                        color = Xwindow::White; // white
                    } else if (chr == 'Z') {
                        color = Xwindow::Red;   // red
                    } else if (chr == 'I') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == 'O') {
                        color = Xwindow::Turquoise;   // red
                    } else if (chr == '*') {
                        color = Xwindow::Brown;   // red
                    } 
                    else{
                        color = Xwindow::Black;   // red
                    }             
                    window->fillRectangle(j * PIXEL_SIZE + window->getWidth()/2 + 5, (21 +i) * PIXEL_SIZE + 2, PIXEL_SIZE, PIXEL_SIZE, color);
                }
            }
            
        }
                    
                }
                
            }
    }
    return;
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
        else if (result == "rename") {
            string prevName;
            string newName;
            in >> prevName;
            in >> newName;
            renameCommand(prevName, newName);
        }
        else if (result == "norandom") { // norandom
            /*
            string seqFile;
            in >> seqFile;
            currentPlayer->level->setFile(seqFile); // set File does not exist at this moment!
            */
        }
        else if (result == "force") {
            /*
            string block;
            in >> block;
            if (isABlock(block)) { // reprompt maybe if it's not  a block
                opponent->setCurrentBlock(block); 
                if (opponent->lost()) {
                    return "WON";
                }
            }*/
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
    else if (result == "rename") {
        if (readingFromFile) {
            return result;
        } 
        else {
            string prevName;
            string newName;
            cin >> prevName;
            cin >> newName;
            renameCommand(prevName, newName);
            }
    }
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
        /////////////currentPlayer->level->setFile(seqFile); // i can't change the file from here...
        
        // pass level seqFile. level knows that if seqFile isn't an empty string then it has to use norandom from now on. otherwise it resets
    }
    else if (isABlock(result)) {
        //currentPlayer->grid->setCurrentBlock(&currentPlayer->playerLevel->generateBlock()); // have to make sure that copy assignment of blocks deletes the old one or smth that works with unique pointers
        // ^^ Guaranteed Memory Leak
    }
    else if (result == "blind") {
        //opponent->grid->blind();
        // ^^ Doesn't exist yet
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
                //opponent->setCurrentBlock(block); 
                // What is lost??
                // if (opponent->lost()) {
                //     return "WON";
                // }
            }
        }
    }
    else {
        matchMultiplied(result, multiplier); // handles all multiplied stuff
    }
    return ""; 
}

void gameController::renameCommand(string curr, string desired) {
  string validMatch = commandMatch(curr); // returns original (command.second)
  if (validMatch == "invalid" || validMatch == "ambiguous") {
    cout << validMatch << endl;
    return;
  }
  string alreadyThere = commandMatch(desired);
  if (alreadyThere != "invalid" && alreadyThere != "ambiguous") {
    // now I need to check if desired is EXACTLY something in the map
    // (command.first) if it is EXACTLY something else then we NEED to say it is
    // already bound
    for (auto it = this->command.begin(); it != this->command.end(); ++it) {
      if (it->first == desired) {
        cout << "The proposed new name is already bound!" << endl;
        return;
      }
    }
  }
  // find the existing command in the map
  // delete this pair from the map and then create a new one with the new name
  // as the key
  // command.first = desired;
  for (auto it = this->command.begin(); it != this->command.end(); ++it) {
    if (it->second == validMatch) {
      this->command.erase(it);
      break;
    }
  }
  command[desired] = validMatch;
  // comment the below out later, just for testing!
  cout << "Renamed " << curr << " to " << desired << endl;
  cout << command[desired] << endl;
}

string gameController::commandMatch(const string &input) {
  string matchedCommand;
  int matchCount = 0;
  bool isAMatch = true;

  for (auto &command : this->command) {
    if (input.length() > command.first.length()) {
      continue;
    }
    for (long unsigned int i = 0; i < input.length(); i++) {
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




