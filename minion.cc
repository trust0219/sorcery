#include "minion.h"
#include "ascii_graphics.h"
#include "board.h"
#include "enchantment.h"
#include "game.h"
#include <iostream>

using namespace std;

Minion::Minion(std::string name, std::string desc, int cost, int att, int def,
               MinionType mt, int mc)
    : Card(name, desc, cost), att(att), def(def), mt(mt), mc(mc) {}

Minion::Minion(Minion &om)
    : Card(om), att(om.att), def(om.def), mt(om.mt), mc(om.mc) {}

Minion::~Minion() {}

void Minion::notify(Game &g, bool p1card, TriggerType tt) {
  MinionType mt = this->getMiniontype();
  string cname = this->getName();
  if (tt == TriggerType::MLB && mt == MinionType::MLB &&
      cname == "Bone Golem") {
    addDef(1);
    addAtt(1);
  } else if (tt == TriggerType::MEB && mt == MinionType::MEB &&
             cname == "Fire Elemental") { // only opponent
    if (p1card && !g.isP1active()) {
      size_t pos = g.getBoard()->getMinions(2).size();
      if (pos > 0) {
        Minion *mt = g.getBoard()->getMinions(2).at(pos - 1);
        mt->addDef(-1);
      }
    } else if (!p1card && g.isP1active()) {
      size_t pos = g.getBoard()->getMinions(1).size();
      if (pos > 0) {
        Minion *mt = g.getBoard()->getMinions(1).at(pos - 1);
        mt->addDef(-1);
      }
    }
  } else if (tt == TriggerType::TE && mt == MinionType::TE &&
             cname == "Potion Seller") {
    if (p1card && g.isP1active()) {
      vector<Minion *> &minions = g.getBoard()->getMinions(1);
      for (Minion *mt : minions) {
        mt->addDef(1);
      }
    } else if (!p1card && !g.isP1active()) {
      vector<Minion *> &minions = g.getBoard()->getMinions(2);
      for (Minion *mt : minions) {
        mt->addDef(1);
      }
    }
  }
}

void Minion::setDef(int n) { def = n; }
void Minion::addDef(int diff) { def += diff; }
void Minion::addAtt(int diff) { att += diff; }
int &Minion::getAttack() { return att; }
int &Minion::getDef() { return def; }
void Minion::refreshAct() { actResource = 1; }
void Minion::addAct(int diff) { actResource += 1; }
void Minion::addActCost(int diff) { actCost += diff; }
void Minion::addMagicCost(int diff) { mc += diff; }
void Minion::unableAct() { ableAct = false; }
CardType Minion::getType() { return CardType::M; }
MinionType Minion::getMiniontype() { return mt; }
int Minion::getMagiccost() { return mc; }
bool Minion::canAbil() { return ableAct; }
bool Minion::useAct() {
  if (actResource >= actCost) {
    actResource -= actCost;
    return true;
  } else {
    return false;
  }
}

card_template_t Minion::display() {
  card_template_t ctt;
  // Display Minion Info
  switch (mt) {
  case MinionType::NTA: // Minion (Normal)
    ctt = display_minion_no_ability(Card::getName(), Card::getCost(), att, def);
    break;

  case MinionType::HA: // Minion (Active)
    ctt = display_minion_activated_ability(Card::getName(), Card::getCost(),
                                           att, def, mc, Card::getDesc());
    break;

  case MinionType::MEB: // Minonio (Trigger)
  case MinionType::MLB:
  case MinionType::TS:
  case MinionType::TE:
    ctt = display_minion_triggered_ability(Card::getName(), Card::getCost(),
                                           att, def, Card::getDesc());
    break;
  default:
    break;
  }
  return ctt;
}

Minion *Minion::getNext() { return nullptr; }
void Minion::setNull() {}
std::vector<card_template_t> Minion::displayEnchantments() {

  std::vector<card_template_t> cttTotal;

  // 1)
  Minion *temp = this;

  // 2)
  // Enchantment *temp = dynamic_cast<Enchantment *>(this);
  while (temp->getNext()) {
    card_template_t ctt =
        display_enchantment(Card::getName(), Card::getCost(), Card::getDesc());
    cttTotal.emplace_back(ctt);
    temp = temp->getNext();
  }

  return cttTotal;
}
