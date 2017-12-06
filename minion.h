#ifndef _MINION_H_
#define _MINION_H_
#include "card.h"
#include "types.h"
#include <string>
#include <vector>

class Minion : public Card {

  // Basic
  int att;
  int def;
  int actResource = 0;
  int actCost = 1;
  MinionType mt;
  int mc; // magic cost
  bool ableAct = true;

public:
  Minion(std::string name, std::string desc, int cost, int att, int def,
         MinionType mt = MinionType::NTA, int mc = 0);
  Minion(Minion &om);

  ~Minion();
  // Trigger
  virtual void notify(Game &g, bool p1card, TriggerType tt);

  // int remainAct();
  int &getAttack();
  int &getDef();
  int getMagiccost();
  void setDef(int n);
  void addAtt(int diff);
  void addDef(int diff);
  void addAct(int diff);
  void addActCost(int diff);
  void addMagicCost(int diff);
  bool useAct();
  bool canAbil();
  void unableAct();
  void refreshAct();
  virtual Minion *getNext();
  virtual CardType getType();
  virtual MinionType getMiniontype();
  virtual void setNull();

  // Display
  virtual std::vector<card_template_t> displayEnchantments();
  virtual card_template_t display();
};

#endif
