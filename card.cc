#include "card.h"
#include "minion.h"
#include "types.h"
#include <iostream>
using namespace std;

Card::Card(std::string name, std::string desc, int cost)
    : name(name), desc(desc), cost(cost) {}

Card::Card(Card &oc) : name(oc.name), desc(oc.desc), cost(oc.cost) {}

Card::~Card() {}

std::string &Card::getName() { return name; }

std::string &Card::getDesc() { return desc; }

int Card::getCost() { return cost; }
