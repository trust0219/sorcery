#ifndef _GAME_H_
#define _GAME_H_

#include "ascii_graphics.h"
#include "enchantment.h"
#include "player.h"
#include "types.h"

class Game {
  Board *pbr;
  Player *p1;
  Player *p2;
  std::vector<Card *> waste;
  bool player1isActive = true;
  bool p1InitialCards = true;
  bool p2InitialCards = true;

public:
  // Big 5
  Game(std::string p1name, std::string p2name,
       std::vector<std::string> &p1cardlist,
       std::vector<std::string> &p2cardlist);
  ~Game();
  // trigger
  void notifyBoard(TriggerType tt);
  // Turn Control
  void turnStart();
  void turnEnd();
  // Accesssor
  Board *getBoard();
  Player *getPlayer(unsigned int pi);
  bool isP1active();
  void gainMagic();
  void draw();

  void play(unsigned int ci, unsigned int pi, unsigned int ti, bool testing);

  void use(unsigned int ci, unsigned int pi, unsigned int ti, bool testing);

  void discard(unsigned int i);

  void attackPlayer(unsigned int i);

  void attackM2M(unsigned int ci, unsigned int cj);

  void processDeathMinions();

  void processDeathPlayer();

  void gameover(unsigned int pi);

  void refreshMinions();

  // Display
  std::vector<card_template_t> inspect(unsigned int i);
  std::vector<card_template_t> showHand();
  std::vector<card_template_t> showBoard(int pi);
};

#endif