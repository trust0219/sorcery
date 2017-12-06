#include "game.h"
#include <iostream>

using namespace std;

Game::Game(std::string p1name, std::string p2name,
           std::vector<std::string> &p1cardlist,
           std::vector<std::string> &p2cardlist)
    : pbr(new Board()), p1(new Player(p1name, p1cardlist)),
      p2(new Player(p2name, p2cardlist)) {}

Game::~Game() {
  delete p1;
  delete p2;
  delete pbr;
}

void Game::gameover(unsigned int pi) {
  cout << "Player " << pi << " is dead now." << endl;
  cout << "Player " << (pi == 1 ? 2 : 1) << "won the game." << endl;
  cout << "Game terminating... Goodbye" << endl;
  exit(1);
}

Board *Game::getBoard() { return pbr; }
Player *Game::getPlayer(unsigned int pi) {
  if (pi == 1) {
    return p1;
  } else {
    return p2;
  }
}

std::vector<card_template_t> Game::showBoard(int pi) { //
  std::vector<card_template_t> boardDisplay;
  if (pi == 1) {
    // p1 rituals
    card_template_t displayP1Ritual = CARD_TEMPLATE_BORDER;
    if (pbr->getRitual(1)) {
      displayP1Ritual = pbr->getRitual(1)->display();
    }
    // update p1 rituals with left column
    for (string &it : displayP1Ritual) {
      it = EXTERNAL_BORDER_CHAR_UP_DOWN + it;
    }
    boardDisplay.emplace_back(displayP1Ritual);
    // blank
    boardDisplay.emplace_back(CARD_TEMPLATE_EMPTY);
    // p1 player info
    card_template_t p1info;
    p1info = p1->display(1);
    boardDisplay.emplace_back(p1info);
    // blank
    boardDisplay.emplace_back(CARD_TEMPLATE_EMPTY);
    // graveyard
    card_template_t displayP1graveyard = CARD_TEMPLATE_BORDER;
    if (pbr->getTopGraveyard(1)) {
      displayP1graveyard = pbr->getTopGraveyard(1)->display();
    }
    // update p1 graveyard with right column
    for (string &it : displayP1graveyard) {
      it = it + EXTERNAL_BORDER_CHAR_UP_DOWN;
    }
    boardDisplay.emplace_back(displayP1graveyard);
    // p1minions
    std::vector<card_template_t> displayP1minions = pbr->displayMinions(1);
    // update p1 minions with left colum and right column
    for (string &it : displayP1minions.front()) {
      it = EXTERNAL_BORDER_CHAR_UP_DOWN + it;
    }
    for (string &it : displayP1minions.back()) {
      it = it + EXTERNAL_BORDER_CHAR_UP_DOWN;
    }
    // copy p1 minions to boardDisplay
    for (auto it : displayP1minions) {
      boardDisplay.emplace_back(it);
    }
    // central SORCERY
    boardDisplay.emplace_back(CENTRE_GRAPHIC);
    return boardDisplay;
  } else { // i == 2
    // p2 minions
    std::vector<card_template_t> displayP2minions = pbr->displayMinions(2);
    // update p2 minions with left colum and right column
    for (string &it : displayP2minions.front()) {
      it = EXTERNAL_BORDER_CHAR_UP_DOWN + it;
    }
    for (string &it : displayP2minions.back()) {
      it = it + EXTERNAL_BORDER_CHAR_UP_DOWN;
    }
    // copy p2 minions to boardDisplay
    for (auto it : displayP2minions) {
      boardDisplay.emplace_back(it);
    }

    // p2 rituals
    card_template_t displayP2Ritual = CARD_TEMPLATE_BORDER;
    if (pbr->getRitual(2)) {
      displayP2Ritual = pbr->getRitual(2)->display();
    }

    // update p2 rituals with left column
    for (string &it : displayP2Ritual) {
      it = EXTERNAL_BORDER_CHAR_UP_DOWN + it;
    }
    boardDisplay.emplace_back(displayP2Ritual);
    // blank
    boardDisplay.emplace_back(CARD_TEMPLATE_EMPTY);
    // p2 player info
    card_template_t p2info;
    p2info = p2->display(2);
    boardDisplay.emplace_back(p2info);
    // blank
    boardDisplay.emplace_back(CARD_TEMPLATE_EMPTY);
    // p2 graveyard
    card_template_t displayP2graveyard = CARD_TEMPLATE_BORDER;
    if (pbr->getTopGraveyard(2)) {
      displayP2graveyard = pbr->getTopGraveyard(2)->display();
    }
    // update p2 graveyard with right column
    for (string &it : displayP2graveyard) {
      it = it + EXTERNAL_BORDER_CHAR_UP_DOWN;
    }
    boardDisplay.emplace_back(displayP2graveyard);

    // final outcome
    return boardDisplay;
  }
}

void Game::draw() {
  if (player1isActive) {
    p1->drawCard(); // deck to hand
  } else {
    p2->drawCard();
  }
}

void Game::gainMagic() {
  if (player1isActive) {
    p1->upMP(1);
  } else {
    p2->upMP(1);
  }
}

void Game::discard(unsigned int i) {
  if (player1isActive) {
    p1->discardCard(i);
  } else {
    p2->discardCard(i);
  }
}

std::vector<card_template_t> Game::inspect(unsigned int i) {
  std::vector<card_template_t> cttTotal;
  if (player1isActive && i <= pbr->getMinions(1).size()) {
    cttTotal.emplace_back(pbr->getMinions(1).at(i - 1)->display());
    // Inserting CARD_TEMPLATE_EMPTY to display enchantments in a next row
    for (int j = 0; j < 4; ++j) {
      cttTotal.emplace_back(CARD_TEMPLATE_EMPTY);
    }
    std::vector<card_template_t> cttEnchantments =
        pbr->getMinions(1).at(i - 1)->displayEnchantments();
    for (auto &it : cttEnchantments) {
      cttTotal.emplace_back(it);
    }
  } else if (i <= pbr->getMinions(2).size()) {
    cttTotal.emplace_back(pbr->getMinions(2).at(i - 1)->display());
    // Inserting CARD_TEMPLATE_EMPTY to display enchantments in a next row
    for (int j = 0; j < 4; ++j) {
      cttTotal.emplace_back(CARD_TEMPLATE_EMPTY);
    }
    Enchantment *pe = dynamic_cast<Enchantment *>(pbr->getMinions(2).at(i - 1));
    std::vector<card_template_t> cttEnchantments = pe->displayEnchantments();
    for (auto &it : cttEnchantments) {
      cttTotal.emplace_back(it);
    }
  }
  return cttTotal;
}

std::vector<card_template_t> Game::showHand() {
  if (player1isActive) {
    return p1->getHandDisplay();
  } else {
    return p2->getHandDisplay();
  }
}

void Game::attackPlayer(unsigned int i) {
  int damage = 0;
  if (player1isActive && i <= pbr->getMinions(1).size() &&
      pbr->getMinions(1).at(i - 1)->useAct()) {
    damage = pbr->getMinions(1).at(i - 1)->getAttack();
    p2->upLife(-damage);
  } else if (!player1isActive && i <= pbr->getMinions(2).size() &&
             pbr->getMinions(2).at(i - 1)->useAct()) {
    damage = pbr->getMinions(2).at(i - 1)->getAttack();
    p1->upLife(-damage);
  }
  processDeathPlayer();
}

void Game::attackM2M(unsigned int ci, unsigned int cj) {
  int damageTo = 0, damageFrom = 0;
  if (player1isActive && ci <= pbr->getMinions(1).size() &&
      cj <= pbr->getMinions(2).size() &&
      pbr->getMinions(1).at(ci - 1)->useAct()) {
    damageTo = pbr->getMinions(1).at(ci - 1)->getAttack();
    pbr->getMinions(2).at(cj - 1)->addDef(-damageTo);
    // attack continues if p2's minion is still alive
    if (pbr->getMinions(2).at(cj - 1)->getDef() > 0) {
      damageFrom = pbr->getMinions(2).at(cj - 1)->getAttack();
      pbr->getMinions(1).at(ci - 1)->addDef(-damageFrom);
    }
    processDeathMinions();
  } else if (!player1isActive && ci <= pbr->getMinions(2).size() &&
             cj <= pbr->getMinions(1).size() &&
             pbr->getMinions(2).at(ci - 1)->useAct()) {
    damageTo = pbr->getMinions(2).at(ci - 1)->getAttack();
    pbr->getMinions(1).at(cj - 1)->addDef(-damageTo);
    processDeathMinions();
    // attack continues if p1's minion is still alive
    if (pbr->getMinions(1).at(cj - 1)->getDef() > 0) {
      damageFrom = pbr->getMinions(1).at(cj - 1)->getAttack();
      pbr->getMinions(2).at(ci - 1)->addDef(-damageFrom);
    }
    processDeathMinions();
  }
}

void Game::processDeathPlayer() {
  if (player1isActive && p1->getLife() <= 0) {
    gameover(1);
  } else if (!player1isActive && p2->getLife() <= 0) {
    gameover(2);
  }
}

bool Game::isP1active() { return player1isActive; }

void Game::play(unsigned int ci, unsigned int pi, unsigned int ti,
                bool testing) {
  if (player1isActive) {
    CardType ct = p1->getCard(ci)->getType();
    switch (ct) {
    case CardType::M: // place Minion
      if (p1->placeMinion(ci, 1, *this)) {
        notifyBoard(TriggerType::MEB);
      }
      break;
    case CardType::S: // do Magic
      p1->useSpell(ci, pi, ti, player1isActive, *this, testing);
      break;
    case CardType::R:
      p1->placeRitual(ci, 1, *this);
      break;
    case CardType::E:
      p1->equipEnchantment(ci, pi, ti, pbr);
      break;
    }
  } else {
    CardType ct = p2->getCard(ci)->getType();
    switch (ct) {
    case CardType::M: // place Minion
      if (p2->placeMinion(ci, 2, *this)) {
        notifyBoard(TriggerType::MEB);
      }
      break;
    case CardType::S: // do Magic
      p2->useSpell(ci, pi, ti, player1isActive, *this, testing);
      break;
    case CardType::R:
      p2->placeRitual(ci, 2, *this);
      break;
    case CardType::E:
      p1->equipEnchantment(ci, pi, ti, pbr);
      break;
    }
  }
  processDeathPlayer();
  processDeathMinions();
}

void Game::processDeathMinions() { // transfer minions < 0 to graveyard
  vector<Minion *> &p1minions = pbr->getMinions(1);
  vector<Minion *> &p2minions = pbr->getMinions(2);

  // Processing Deaths of Minions && Trigger Minion Leave Board
  if (player1isActive) {
    for (size_t i = 1; i <= p1minions.size(); ++i) {
      if (p1minions.at(i - 1)->getDef() <= 0) {
        pbr->transferBoardToGraveyard(1, i);
        notifyBoard(TriggerType::MLB);
      }
    }
    for (size_t j = 1; j <= p2minions.size(); ++j) {
      if (p2minions.at(j - 1)->getDef() <= 0) {
        pbr->transferBoardToGraveyard(2, j);
        notifyBoard(TriggerType::MLB);
      }
    }
  } else {
    for (size_t j = 1; j <= p2minions.size(); ++j) {
      if (p2minions.at(j - 1)->getDef() <= 0) {
        pbr->transferBoardToGraveyard(2, j);
        notifyBoard(TriggerType::MLB);
      }
    }
    for (size_t i = 1; i <= p1minions.size(); ++i) {
      if (p1minions.at(i - 1)->getDef() <= 0) {
        pbr->transferBoardToGraveyard(1, i);
        notifyBoard(TriggerType::MLB);
      }
    }
  }
}

// Use Minion's Ability
void Game::use(unsigned int ci, unsigned int pi, unsigned int ti,
               bool testing) {
  if (player1isActive) { // Player 1
    MinionType mt = pbr->getMinions(1).at(ci - 1)->getMiniontype();
    string cname = pbr->getMinions(1).at(ci - 1)->getName();
    int abilcost = pbr->getMinions(1).at(ci - 1)->getMagiccost();
    Minion *pm = pbr->getMinions(1).at(ci - 1);
    if (mt == MinionType::HA) {
      if (!testing || p1->getMP() <= abilcost) { // can't use act ability
        return;
      }
      if (!pm->canAbil()) {
        return;
      }
      if (p1->getMP() >= abilcost) { // mp reduction
        p1->upMP(-abilcost);
      }
      if (cname == "Novice Pyromancer") {
        Minion *target = pbr->getMinions(pi).at(ti - 1);
        target->addDef(-1);
      } else if (cname == "Apprentice Summoner") { // Summon 1 Air Elemental
        size_t pos = pbr->getMinions(1).size();
        if (pos < 5) {
          Minion *newmini = new Minion("Air Elemental", "", 0, 1, 1);
          pbr->getMinions(1).emplace_back(newmini);
          notifyBoard(TriggerType::MEB);
        }
      } else if (cname == "Master Summoner") { // Summon up to 3 Air Elementals
        size_t pos = pbr->getMinions(1).size();
        unsigned int count = 0;
        while (pos < 5 && count < 3) {
          Minion *newmini = new Minion("Air Elemental", "", 0, 1, 1);
          pbr->getMinions(1).emplace_back(newmini);
          notifyBoard(TriggerType::MEB);
          pos++;
          count++;
        }
      }
    }
  } else { // Player 2
    MinionType mt = pbr->getMinions(2).at(ci - 1)->getMiniontype();
    string cname = pbr->getMinions(2).at(ci - 1)->getName();
    int abilcost = pbr->getMinions(2).at(ci - 1)->getMagiccost();
    Minion *pm = pbr->getMinions(2).at(ci - 1);
    if (mt == MinionType::HA) {
      if (!testing || p2->getMP() <= abilcost) { // can't use act ability
        return;
      }
      if (!pm->canAbil()) {
        return;
      }
      if (p2->getMP() >= abilcost) { // mp reduction
        p2->upMP(-abilcost);
      }
      if (cname == "Novice Pyromancer") {
        Minion *target = pbr->getMinions(pi).at(ti - 1);
        target->addDef(-1);
      } else if (cname == "Apprentice Summoner") { // Summon 1 Air Elemental
        size_t pos = pbr->getMinions(2).size();
        if (pos < 5) {
          // pbr->getMinions(2).at(pos) = new Minion("Air Elemental", "", 0, 1,
          // 1);
          Minion *newmini = new Minion("Air Elemental", "", 0, 1, 1);
          pbr->getMinions(2).emplace_back(newmini);
          notifyBoard(TriggerType::MEB);
        }
      } else if (cname == "Master Summoner") { // Summon up to 3 Air Elementals
        size_t pos = pbr->getMinions(2).size();
        unsigned int count = 0;
        while (pos < 5 && count < 3) {
          Minion *newmini = new Minion("Air Elemental", "", 0, 1, 1);
          pbr->getMinions(2).emplace_back(newmini);
          // pbr->getMinions(2).at(pos) = new Minion("Air Elemental", "", 0, 1,
          // 1);
          notifyBoard(TriggerType::MEB);
          pos++;
          count++;
        }
      }
    }
  }
  processDeathPlayer();
  processDeathMinions();
}

void Game::notifyBoard(TriggerType tt) {

  // if (tt == TriggerType::MEB) {
  //   cout << "MEB";
  // }
  // cout << endl;
  // virtual void notify(Game &g, bool p1card, TriggerType tt);
  if (player1isActive) {
    for (Minion *ptr_m : pbr->getMinions(1)) {
      ptr_m->notify(*this, true, tt);
    }
    if (pbr->getRitual(1)) {
      pbr->getRitual(1)->notify(*this, true, tt);
    }
    for (Minion *ptr_m : pbr->getMinions(2)) {
      ptr_m->notify(*this, false, tt);
    }
    if (pbr->getRitual(2)) {
      pbr->getRitual(2)->notify(*this, false, tt);
    }
  } else {
    for (Minion *ptr_m : pbr->getMinions(2)) {
      ptr_m->notify(*this, false, tt);
    }
    if (pbr->getRitual(2)) {
      pbr->getRitual(2)->notify(*this, false, tt);
    }
    for (Minion *ptr_m : pbr->getMinions(1)) {
      ptr_m->notify(*this, true, tt);
    }
    if (pbr->getRitual(1)) {
      pbr->getRitual(1)->notify(*this, true, tt);
    }
  }
}

void Game::turnStart() {
  // gains magic
  gainMagic();
  // Every Minion's action set to 1 (APNAP)
  refreshMinions();
  // draw a card
  if (p1InitialCards) {
    draw();
    draw();
    draw();
    draw();
    draw();
    p1InitialCards = false;
  } else if (p2InitialCards) {
    draw();
    draw();
    draw();
    draw();
    draw();
    p2InitialCards = false;
  } else {
    draw();
  }

  // At the Start of Turn
  notifyBoard(TriggerType::TS);
}

void Game::turnEnd() {
  // At the End of Turn
  notifyBoard(TriggerType::TE);
  // Active Player changes
  player1isActive = !player1isActive;
  // Next player starts
  turnStart();
}

void Game::refreshMinions() {
  if (player1isActive) {
    vector<Minion *> &minions = pbr->getMinions(1);
    for (Minion *pm : minions) {
      pm->refreshAct();
    }
  } else {
    vector<Minion *> &minions = pbr->getMinions(2);
    for (Minion *pm : minions) {
      pm->refreshAct();
    }
  }
}