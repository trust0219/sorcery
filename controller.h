#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "ascii_graphics.h"
#include "game.h"

class Controller {
  bool testing = false, graphics = false;

public:
  Controller(bool testing, bool graphics);
  // methods
  void processor(std::istream &in, Game &g);
  void shuffle(std::vector<std::string> &rdeck);
  void printHelp();
  void takeName(std::istream &in, std::string &name1, std::string &name2);
  // Display
  void displayCards(std::vector<card_template_t> cttVec);
  void displayHalfBoard(std::vector<card_template_t> cttVec, int pi);
  std::vector<card_template_t> cardsInRow(std::vector<card_template_t> cttVec);
};

#endif