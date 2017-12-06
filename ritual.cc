#include "ritual.h"
#include "game.h"
#include <iostream>
using namespace std;

Ritual::Ritual(std::string name, std::string desc, int cost,
               TriggerType tt_ritual, int ritual_cost, int ritual_charges)
    : Card(name, desc, cost), ritual_cost(ritual_cost),
      ritual_charges(ritual_charges), tt_ritual(tt_ritual) {}

Ritual::Ritual(Ritual &other)
    : Card(other), ritual_cost(other.ritual_cost),
      ritual_charges(other.ritual_charges), tt_ritual(other.tt_ritual) {}

void Ritual::notify(Game &g, bool p1card, TriggerType tt) {
  if (Card::getName() == "Dark Ritual" && tt == TriggerType::TS) {
    if (!processCostAndCharges()) {
      return;
    }
    if (p1card && g.isP1active()) {
      g.getPlayer(1)->upMP(1);
    } else if (!p1card && !g.isP1active()) {
      g.getPlayer(2)->upMP(1);
    }
  } else if (Card::getName() == "Aura of Power" && tt == TriggerType::MEB) {
    if (p1card && g.isP1active()) {
      if (!processCostAndCharges()) {
        return;
      }
      g.getBoard()->getMinions(1).back()->addAtt(1);
      g.getBoard()->getMinions(1).back()->addDef(1);
    } else if (!p1card && !g.isP1active()) {
      if (!processCostAndCharges()) {
        return;
      }
      g.getBoard()->getMinions(2).back()->addAtt(1);
      g.getBoard()->getMinions(2).back()->addDef(1);
    }
  }
  // Standstill implemented in player.cc
}

card_template_t Ritual::display() {
  return display_ritual(Card::getName(), Card::getCost(), ritual_cost,
                        Card::getDesc(), ritual_charges);
}

void Ritual::upCharge(int n) { ritual_charges += n; }
CardType Ritual::getType() { return CardType::R; }
TriggerType Ritual::getRitualType() { return tt_ritual; }
bool Ritual::processCostAndCharges() {
  if (ritual_charges >= ritual_cost) {
    ritual_charges -= ritual_cost;
    return true;
  } else {
    return false;
  }
}
