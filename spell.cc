#include "spell.h"
#include "game.h"
#include <string>

Spell::Spell(std::string name, std::string desc, int cost)
    : Card(name, desc, cost) {}

Spell::~Spell() {}

void Spell::notify(Game &g, bool p1card, TriggerType tt) {}

card_template_t Spell::display() {
  return display_spell(Card::getName(), Card::getCost(), Card::getDesc());
}

CardType Spell::getType() { return CardType::S; }