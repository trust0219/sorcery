#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>

#include "board.h"
#include "card.h"

class Game;
class Board;

class Player {
  std::string name;
  std::vector<Card *> hand;
  std::vector<Card *> deck;
  // Board *ptr_b;
  int life = 20;
  int mp = 100; // testing (original : 3)

public:
  Player(std::string name, std::vector<std::string> &cardlist);
  ~Player();
  void upMP(int diff);
  void upLife(int diff);
  void drawCard();
  void discardCard(unsigned int i);
  bool useMP(int mp_use);
  bool placeMinion(unsigned int ci, unsigned int pi, Game &g);
  bool placeRitual(unsigned int ci, unsigned int pi, Game &g);

  void useSpell(unsigned int ci, unsigned int pi, unsigned int ti,
                bool p1active, Game &g, bool testing);

  void equipEnchantment(unsigned int ci, unsigned int pi, unsigned int ti,
                        Board *pbr);

  Card *getCard(unsigned int ci);

  std::string &getName();
  std::vector<Card *> &getHand();
  int getLife();
  int getMP();

  // Display
  std::vector<card_template_t> getHandDisplay();
  card_template_t display(int pi);
};

#endif