#include "controller.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Controller::Controller(bool testing, bool graphics)
    : testing(testing), graphics(graphics) {}

void Controller::shuffle(std::vector<std::string> &rdeck) {
  for (size_t i = 0; i < rdeck.size(); ++i) {
    size_t r = i + rand() % (rdeck.size() - i);
    swap(rdeck.at(i), rdeck.at(r));
  }
}

void Controller::printHelp() { cout << "-- help message" << endl; }

void Controller::displayCards(std::vector<card_template_t> cttVec) {
  // slice into 5 card_template_t
  for (unsigned int i = 0; i < cttVec.size(); i += 5) {
    if (cttVec.size() - i > 5) {
      vector<card_template_t> sliced(cttVec.begin() + i,
                                     cttVec.begin() + i + 5);
      sliced = cardsInRow(sliced);
      for (auto &row : sliced) {
        for (auto &s : row) {
          cout << s;
        }
        cout << endl;
      }
    } else {
      vector<card_template_t> sliced(cttVec.begin() + i, cttVec.end());
      sliced = cardsInRow(sliced);
      for (auto &row : sliced) {
        for (auto &s : row) {
          cout << s;
        }
        cout << endl;
      }
    }
  }
}

std::vector<card_template_t>
Controller::cardsInRow(std::vector<card_template_t> cttVec) {
  vector<card_template_t> rearranged;
  rearranged.resize(cttVec.at(0).size());
  for (size_t i = 0; i < rearranged.size(); ++i) {
    rearranged.at(i).resize(cttVec.size());
  }
  for (size_t i = 0; i < cttVec.size(); ++i) {
    for (size_t j = 0; j < cttVec.at(0).size(); ++j) {
      rearranged.at(j).at(i) = cttVec.at(i).at(j);
    }
  }
  return rearranged;
}

void Controller::takeName(std::istream &in, std::string &name1,
                          std::string &name2) {
  getline(in, name1);
  getline(in, name2);
}

void Controller::displayHalfBoard(std::vector<card_template_t> cttVec, int pi) {
  const unsigned int rowBlocks = 167;
  if (pi == 1) {
    // Display Border - Top
    for (unsigned int i = 0; i < rowBlocks; ++i) {
      cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << endl;
    Controller::displayCards(cttVec);
  } else {
    Controller::displayCards(cttVec);
    // Display Border - Bottom
    for (unsigned int i = 0; i < rowBlocks; ++i) {
      cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << endl;
  }
}

void Controller::processor(std::istream &in, Game &g) {
  // Graphics
  if (graphics) {
  }

  // Parsing Commands
  string command;

  while (getline(in, command)) {
    try {
      // **************************** TESTING
      cout << "command repeat: {" << command << "}" << endl;
      // **************************** TESTING
      // single command
      unsigned int n1, n2, n3;
      string tpart = "";
      if (command == "quit") {
        break;
      } else if (command == "help") {
        printHelp();
      } else if (command == "end") {
        g.turnEnd();
      } else if (command == "draw" && testing) {
        g.draw();
      } else { // multiple command
        istringstream iss{command};
        string partialCmd;
        while (iss >> partialCmd) {
          if (partialCmd == "discard") {
            if (iss >> n1 && testing) {
              g.discard(n1); // discard {i}
            }
          } else if (partialCmd == "attack") {
            if (iss >> n1 >> n2) { // attack {i} {j}
              g.attackM2M(n1, n2);
            } else {
              g.attackPlayer(n1); // attack {i}
            }
          } else if (partialCmd == "play") {
            if (iss >> n1 >> n2 >> tpart) {
              stringstream ss{tpart};
              if (ss >> n3) { // play {i} {p} {t}:target minoin
                ss.clear();
                g.play(n1, n2, n3, testing);
              } else { // play {i} {p} {t}:ritual
                ss.clear();
                g.play(n1, n2, 0, testing);
              }
            } else { // play {i}
              g.play(n1, 0, 0, testing);
            }
          } else if (partialCmd == "use") {
            if (iss >> n1 >> n2 >> tpart) {
              stringstream ss{tpart};
              if (ss >> n3) { // use {i} {p} {t}:target minoin
                ss.clear();
                g.use(n1, n2, n3, testing);
              } else { // use {i} {p} {t}:ritual
                ss.clear();
                g.use(n1, n2, 'r', testing);
              }
            } else { // use {i}
              g.use(n1, 0, 0, testing);
            }
          } else if (partialCmd == "inspect" && iss >> n1) { // inspect {i}
            displayCards(g.inspect(n1));
          } else if (partialCmd == "hand") {
            displayCards(g.showHand());
          } else if (partialCmd == "board") {
            displayHalfBoard(g.showBoard(1), 1);
            displayHalfBoard(g.showBoard(2), 2);
          }
        }
      }
      n1 = n2 = n3 = 0; // Default-ify
      command.clear();
    } catch (out_of_range) {
      cerr << "Your input is our of range. Try again." << endl;
    }
  }
}
