#ifndef _RITUAL_H_
#define _RITUAL_H_

#include "ascii_graphics.h"
#include "card.h"
#include "types.h"

class Ritual : public Card {
  int ritual_cost;
  int ritual_charges;
  TriggerType tt_ritual;

public:
  Ritual(std::string name, std::string desc, int cost, TriggerType tt_tirual,
         int ritual_cost, int ritual_charges);
  Ritual(Ritual &other);

  bool processCostAndCharges();
  CardType getType();
  TriggerType getRitualType();
  virtual void notify(Game &g, bool p1card, TriggerType tt);
  virtual card_template_t display();
  void upCharge(int n);
};

#endif