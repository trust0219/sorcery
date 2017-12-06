#ifndef _CARD_H_
#define _CARD_H_

#include "ascii_graphics.h"
#include "types.h"
#include <string>

class Game;

class Card {
  std::string name;
  std::string desc;
  int cost;

public:
  Card(std::string name, std::string desc, int cost);
  Card(Card &oc);
  virtual ~Card();
  // pure virtual methods
  virtual void notify(Game &g, bool p1card, TriggerType tt) = 0;
  virtual card_template_t display() = 0;
  virtual CardType getType() = 0;
  //
  std::string &getName();
  std::string &getDesc();
  int getCost();
};
#endif