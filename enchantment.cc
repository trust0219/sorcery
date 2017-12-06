#include "enchantment.h"
#include <iostream>
#include <string>
using namespace std;

Enchantment::Enchantment(std::string name, std::string desc, int cost, int att,
                         int def, MinionType mt, int mc)
    : Minion(name, desc, cost, att, def, mt, mc) {}

Enchantment::Enchantment(std::string ename, std::string edesc, int ecost,
                         Minion *pm)
    : Minion(*pm), ename(ename), edesc(edesc), ecost(ecost), pm(pm) {
  if (ename == "Giant Strength") {
    Minion::getAttack() += 2;
    Minion::getDef() += 2;
  } else if (ename == "Enrage") {
    Minion::getAttack() *= 2;
    Minion::getDef() *= 2;
  } else if (ename == "Haste") {
    Minion::addAct(1);
  } else if (ename == "Silence") {
    Minion::unableAct();
  } else if (ename == "Magic Fatigue") {
    Minion::addMagicCost(2);
  }
}

Enchantment::~Enchantment() { delete pm; }

Enchantment *Enchantment::getNext() { return dynamic_cast<Enchantment *>(pm); }

CardType Enchantment::getType() { return CardType::E; }

MinionType Enchantment::getMiniontype() {
  Minion *temp = pm;
  while (temp->getNext()) {
    temp = temp->getNext();
  }
  MinionType mt = temp->getMiniontype();
  return mt;
}

void Enchantment::setNull() { pm = nullptr; }

void Enchantment::notify(Game &g, bool p1card, TriggerType tt) {
  if (Minion::getName() == "Haste" && tt == TriggerType::TS) {
    Minion::addAct(1);
  }
  Minion::notify(g, p1card, tt);
}

// Display
card_template_t Enchantment::display() {
  string cname = Card::getName();
  if (pm) { // display Enchanted Minion
    return Minion::display();
  } else if (cname == "Giant Strength") {
    return display_enchantment_attack_defence(Card::getName(), Card::getCost(),
                                              Card::getDesc(), "+2", "+2");
  } else if (cname == "Enrage") {
    return display_enchantment_attack_defence(Card::getName(), Card::getCost(),
                                              Card::getDesc(), "*2", "*2");
  } else { // other cases (modify later)
    return display_enchantment(Card::getName(), Card::getCost(),
                               Card::getDesc());
  }
}

std::vector<card_template_t> Enchantment::displayEnchantments() {
  std::vector<card_template_t> cttTotal;
  // Initial Enchanment
  card_template_t ctt = Enchantment::displayEnchantonly();
  cttTotal.emplace_back(ctt);
  Enchantment *temp = dynamic_cast<Enchantment *>(pm);
  while (temp) {
    ctt = temp->displayEnchantonly();
    cttTotal.emplace(cttTotal.begin(), ctt);
    // cttTotal.emplace_back(ctt);
    temp = temp->getNext();
  }
  return cttTotal;
}

card_template_t Enchantment::displayEnchantonly() {
  if (ename == "Giant Strength") {
    return display_enchantment_attack_defence(ename, ecost, "", "+2", "+2");
  } else if (ename == "Enrage") {
    return display_enchantment_attack_defence(ename, ecost, "", "*2", "*2");
  } else { // other cases (modify later)
    return display_enchantment(ename, ecost, edesc);
  }
}