#ifndef _SPELL_H_
#define _SPELL_H_

#include "ascii_graphics.h"
#include "card.h"
#include "types.h"

class Game;

class Spell : public Card {

public:
  Spell(std::string name, std::string desc, int cost);
  Spell(Spell &os);
  ~Spell();
  // virtual methods
  virtual void notify(Game &g, bool p1card, TriggerType tt);
  virtual card_template_t display();
  virtual CardType getType();
};

#endif
