#include "board.h"
#include "ascii_graphics.h"
#include "game.h"
#include <iostream>
using namespace std;

Board::~Board() {
  for (auto m1 : p1minions) {
    delete m1;
  }
  for (auto m2 : p2minions) {
    delete m2;
  }
  for (auto m1 : p1graveyard) {
    delete m1;
  }
  for (auto m2 : p2graveyard) {
    delete m2;
  }
  delete p1ritual;
  delete p2ritual;
}

std::vector<Minion *> &Board::getMinions(unsigned int pi) {
  if (pi == 1)
    return p1minions;
  else
    return p2minions;
}

Ritual *Board::getRitual(unsigned int pi) {
  if (pi == 1)
    return p1ritual;
  else
    return p2ritual;
}

Minion *Board::getTopGraveyard(unsigned int pi) {
  if (pi == 1) {
    if (p1graveyard.size() > 0) {
      return p1graveyard.back();
    } else {
      return nullptr;
    }
  } else {
    if (p2graveyard.size() > 0) {
      return p2graveyard.back();
    } else {
      return nullptr;
    }
  }
}

// void Board::notifyMinionsAndRituals(bool p1active, TriggerType tt) {
// if (p1active) {

//   for (Minion *ptr_m : p1minions) { // notify p1's minions && rituals first
//     ptr_m->notify(this, p1active, true, tt);
//   }

//   if (p1ritual) {
//     p1ritual->notify(this, p1active, true, tt);
//   }

//   for (Minion *ptr_m : p2minions) { // notify p2's later
//     ptr_m->notify(this, p1active, false, tt);
//   }

//   if (p2ritual) {
//     p2ritual->notify(this, p1active, false, tt);
//   }

// } else {

//   for (Minion *ptr_m : p2minions) { // notify p2's first
//     ptr_m->notify(this, p1active, false, tt);
//   }

//   if (p2ritual) {
//     p2ritual->notify(this, p1active, false, tt);
//   }

//   for (Minion *ptr_m : p1minions) { // notify p1's later
//     ptr_m->notify(this, p1active, true, tt);
//   }

//   if (p1ritual) {
//     p1ritual->notify(this, p1active, true, tt);
//   }
// }
//}

std::vector<card_template_t> Board::displayMinions(int pi) {
  std::vector<card_template_t> cttTotal;
  size_t i;
  if (pi == 1) {
    for (i = 0; i < p1minions.size(); ++i) {
      cttTotal.emplace_back(p1minions.at(i)->display());
    }
    while (i++ < 5) {
      cttTotal.emplace_back(CARD_TEMPLATE_BORDER);
    }
  }

  else { // i == 2
    for (i = 0; i < p2minions.size(); ++i) {
      cttTotal.emplace_back(p2minions.at(i)->display());
    }
    while (i++ < 5) {
      cttTotal.emplace_back(CARD_TEMPLATE_BORDER);
    }
  }
  return cttTotal;
}

void Board::transferBoardToGraveyard(unsigned int pi, unsigned int ti) {
  if (pi == 1) {
    p1graveyard.emplace_back(p1minions.at(ti - 1));
    p1minions.erase(p1minions.begin() + ti - 1);
  } else {
    p2graveyard.emplace_back(p2minions.at(ti - 1));
    p2minions.erase(p2minions.begin() + ti - 1);
  }
}

void Board::destoryNewMinion(unsigned int pi) {
  unsigned int ti;
  if (pi == 1) {
    ti = p1minions.size();
  } else {
    ti = p2minions.size();
  }
  transferBoardToGraveyard(pi, ti);
}

void Board::transferGraveyardToBoard(unsigned int pi) {
  if (pi == 1 && p1graveyard.size() > 0) {
    p1minions.emplace_back(p1graveyard.back());
    p1minions.back()->setDef(1);
    p1graveyard.pop_back();
  } else if (p2graveyard.size() > 0) {
    p2minions.emplace_back(p2graveyard.back());
    p2minions.back()->setDef(1);
    p2graveyard.pop_back();
  }
}

void Board::assignRitual(unsigned int pi, Ritual *ptr_r) {
  if (pi == 1) {
    p1ritual = ptr_r;
  } else {
    p2ritual = ptr_r;
  }
}

void Board::removeRitual(unsigned int pi) {
  if (pi == 1) {
    delete p1ritual;
    p1ritual = nullptr;
  } else {
    delete p2ritual;
    p2ritual = nullptr;
  }
}