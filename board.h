#ifndef _BOARD_H_
#define _BOARD_H_

#include "card.h"
#include "minion.h"
#include "ritual.h"
#include "spell.h"
#include <vector>

class Board {
  std::vector<Minion *> p1minions;
  std::vector<Minion *> p2minions;
  std::vector<Minion *> p1graveyard;
  std::vector<Minion *> p2graveyard;
  Ritual *p1ritual = nullptr;
  Ritual *p2ritual = nullptr;

public:
  Board() = default;
  ~Board();
  //
  void transferBoardToGraveyard(unsigned int pi, unsigned int ti);
  void transferGraveyardToBoard(unsigned int pi);
  void destoryNewMinion(unsigned int pi);
  void assignRitual(unsigned int pi, Ritual *ptr_r);
  void removeRitual(unsigned int pi);
  // void notifyMinionsAndRituals(bool p1active, TriggerType tt);
  //
  std::vector<Minion *> &getMinions(unsigned int pi);
  Ritual *getRitual(unsigned int pi);
  Minion *getTopGraveyard(unsigned int pi);
  // Display
  std::vector<card_template_t> displayMinions(int pi);
};
#endif