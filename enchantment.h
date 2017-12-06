#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_

#include "card.h"
#include "minion.h"

class Enchantment : public Minion {
  std::string ename;
  std::string edesc;
  int ecost;
  Minion *pm = nullptr;

public:
  Enchantment(std::string name, std::string desc, int cost, int att, int def,
              MinionType mt, int mc);
  Enchantment(std::string ename, std::string edesc, int ecost, Minion *pm);
  ~Enchantment();
  //
  virtual void notify(Game &g, bool p1card, TriggerType tt);
  virtual void setNull();
  //
  Enchantment *getNext();
  virtual CardType getType();
  virtual MinionType getMiniontype();
  // Display
  virtual card_template_t display();
  virtual std::vector<card_template_t> displayEnchantments();
  virtual card_template_t displayEnchantonly();
};
#endif