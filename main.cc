#include "ascii_graphics.h"
#include "controller.h"
#include "errormsg.h"
#include "game.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  // **************************** TESTING
  // Echo the arguments for Testing Purpose
  cout << "Your Command Line Arguments: ";
  for (int i = 1; i < argc; ++i) {
    cout << argv[i] << " ";
  }
  cout << endl;
  // **************************** TESTING

  // Stage 1: parse the command line arguments
  string deck1name = "default.deck", deck2name = "default.deck", initName = "";
  bool testing = false, graphics = false;
  ifstream deck1file, deck2file, initFile;
  for (int i = 1; i < argc; ++i) {
    string cmdarg{argv[i]};
    if (cmdarg == "-deck1") {
      deck1name = argv[++i];      // read next argument as file
      deck1file.open(deck1name);  // try to open before continuing
      if (!deck1file.is_open()) { // can't open
        invalidFileError(deck1name);
      }
    } else if (cmdarg == "-deck2") {
      deck2name = argv[++i];
      deck2file.open(deck2name);
      if (!deck2file.is_open()) {
        invalidFileError(deck2name);
      }
    } else if (cmdarg == "-init") {
      initName = argv[++i];
      initFile.open(initName);
      if (!initFile.is_open()) {
        invalidFileError(initName);
      }
    } else if (cmdarg == "-testing") {
      testing = true;
    } else if (cmdarg == "-graphics") {
      graphics = true;
    } else {
      invalidArgumentError(cmdarg);
    }
  }

  if (deck1name == "default.deck") { // Setting to default Deck
    deck1file.open(deck1name);
  }
  if (deck2name == "default.deck") {
    deck2file.open(deck2name);
  }

  Controller ctrl(testing, graphics);
  // State 2: Ask for Names
  string p1name, p2name;

  // ask for name
  if (initName != "") { // no -init
    ctrl.takeName(initFile, p1name, p2name);
  } else { // -init
    ctrl.takeName(cin, p1name, p2name);
  }

  // Stage 3: Shuffling Decks (changing word orders of deckfiles)
  // Shuffling Success

  srand(time(nullptr));
  string c;
  vector<string> deck1;
  vector<string> deck2;
  while (getline(deck1file, c)) {
    deck1.emplace_back(c);
  }
  while (getline(deck2file, c)) {
    deck2.emplace_back(c);
  }
  // Shuffle the decks (ON / OFF - for testing)
  if (!testing) {
    ctrl.shuffle(deck1);
    ctrl.shuffle(deck2);
  }
  // Stage 4: Set the Game
  Game g(p1name, p2name, deck1, deck2);

  // Stage 5: Game Starts

  string command;
  g.turnStart();

  // Stage 6: Take Commands
  // upgrade to controlller so that it can take istream& => cin ,fin

  // fin with initFile
  if (initName != "") {
    ctrl.processor(initFile, g);
  }
  // cin
  ctrl.processor(cin, g);
}