#include "player.h"
#include "ascii_graphics.h"
#include "board.h"
#include "enchantment.h"
#include "game.h"
#include <fstream>
#include <iostream>
using namespace std;

Player::Player(std::string name, std::vector<std::string> &cardlist)
    : name(name) {
  string cname, description = "";

  Card *ptr_c;
  for (auto &cname : cardlist) {
    // Minions
    if (cname == "Air Elemental") {
      description = "";
      ptr_c = new Minion(cname, description, 0, 1, 1);
    } else if (cname == "Earth Elemental") {
      description = "";
      ptr_c = new Minion(cname, description, 3, 4, 4);
    } else if (cname == "Bone Golem") {
      description = "Gain +1/+1 whenever a minion leaves play";
      ptr_c = new Minion(cname, description, 2, 1, 3, MinionType::MLB);
    } else if (cname == "Fire Elemental") {
      description =
          "Whenever an opponent's minion enters play, deal 1 damage to it.";
      ptr_c = new Minion(cname, description, 2, 2, 2, MinionType::MEB);
    } else if (cname == "Potion Seller") {
      description = "At the end of your turn, all your minions gain +0/+1";
      // MinionType is problem
      ptr_c = new Minion(cname, description, 2, 1, 3, MinionType::TE);
    } else if (cname == "Novice Pyromancer") {
      description = "Deal 1 damage to target minion";
      ptr_c = new Minion(cname, description, 1, 0, 1, MinionType::HA, 1);
    } else if (cname == "Apprentice Summoner") {
      description = "Summon a 1/1 air elemental";
      ptr_c = new Minion(cname, description, 1, 1, 1, MinionType::HA, 1);
    } else if (cname == "Master Summoner") {
      description = "Summon up to three 1/1 air elementals";
      ptr_c = new Minion(cname, description, 3, 3, 2, MinionType::HA, 2);
    }
    // Spell
    else if (cname == "Banish") {
      description = "Destroy target minion or ritual";
      ptr_c = new Spell(cname, description, 2);
    } else if (cname == "Unsummon") {
      description = "Return target minion to its owner's hand";
      ptr_c = new Spell(cname, description, 1);
    } else if (cname == "Recharge") {
      description = "Your ritual gains 3 charges";
      ptr_c = new Spell(cname, description, 1);
    } else if (cname == "Disenchant") {
      description = "Destroy the top enchantment on target minion";
      ptr_c = new Spell(cname, description, 1);
    } else if (cname == "Raise Dead") {
      description =
          "Resurrect the top minion in your graveyard and set its def to 1";
      ptr_c = new Spell(cname, description, 1);
    } else if (cname == "Blizzard") {
      description = "Deal 2 damage to all minions";
      ptr_c = new Spell(cname, description, 3);
    }
    // Enchantment
    else if (cname == "Giant Strength") {
      description = "";
      ptr_c = new Enchantment(cname, description, 1, 0, 0, MinionType::ENC, 0);
    } else if (cname == "Enrage") {
      description = "";
      ptr_c = new Enchantment(cname, description, 2, 0, 0, MinionType::ENC, 0);
    } else if (cname == "Haste") {
      description = "Enchanted minion gains +1 action each turn";
      ptr_c = new Enchantment(cname, description, 1, 0, 0, MinionType::ENC, 0);
    } else if (cname == "Magic Fatigue") {
      description = "Enchanted minion's activated ability costs 2 more";
      ptr_c = new Enchantment(cname, description, 0, 0, 0, MinionType::ENC, 0);
    } else if (cname == "Silence") {
      description = "Enchanted minion cannot use abilities";
      ptr_c = new Enchantment(cname, description, 1, 0, 0, MinionType::ENC, 0);
    }
    // Ritual
    /*
    Ritual(std::string name, std::string desc, int cost, TriggerType tt_tirual,
         int ritual_cost, int ritual_charges);

     */
    else if (cname == "Dark Ritual") {
      description = "At the start of your turn, gain 1 magic.";
      ptr_c = new Ritual(cname, description, 0, TriggerType::TS, 1, 5);
    } else if (cname == "Aura of Power") {
      description =
          "Whenever a minion enters play under your control, it gains +1/+1.";
      ptr_c = new Ritual(cname, description, 1, TriggerType::MEB, 1, 4);
    } else if (cname == "Standstill") {
      description = "Whenever a minion enters play, destory it.";
      ptr_c = new Ritual(cname, description, 3, TriggerType::MEB, 2, 3);
    }

    deck.emplace_back(ptr_c); // Insert a card into a deck
  }
}

Player::~Player() {
  for (auto handcard : hand) {
    delete handcard;
  }
  for (auto deckcard : deck) {
    delete deckcard;
  }
}

std::string &Player::getName() { return name; }
void Player::upMP(int diff) { mp += diff; }
void Player::upLife(int diff) { life += diff; }
int Player::getMP() { return mp; }

void Player::drawCard() {
  if (hand.size() < 5 && deck.size() > 0) {
    hand.emplace_back(deck.back());
    deck.pop_back();
  }
}

int Player::getLife() { return life; }

void Player::discardCard(unsigned int i) {
  if (hand.size() > 0 && i <= hand.size()) {
    Card *ptr_c = hand.at(i - 1);
    hand.erase(hand.begin() + i - 1);
    delete ptr_c;
  }
}

std::vector<card_template_t> Player::getHandDisplay() {
  std::vector<card_template_t> cttVec;
  for (Card *pc : hand) {
    cttVec.emplace_back(pc->display());
  }
  if (hand.size() == 0) { // Testing
  }
  return cttVec;
}

/*
card_template_t display_player_card(int player_num, std::string name, int life,
                                    int mana);
*/
card_template_t Player::display(int pi) {
  if (pi == 1)
    return display_player_card(1, name, life, mp);
  else
    return display_player_card(2, name, life, mp);
}

Card *Player::getCard(unsigned int ci) {
  Card *submission = hand.at(ci - 1);
  return submission;
}

std::vector<Card *> &Player::getHand() { return hand; }
bool Player::useMP(int mp_use) {
  if (mp >= mp_use) {
    mp -= mp_use;
    return true;
  } else {
    return false;
  }
}

bool Player::placeRitual(unsigned int ci, unsigned int pi, Game &g) {
  // MP reduction
  Card *pc = hand.at(ci - 1);
  int summoncost = pc->getCost();
  if (useMP(summoncost)) {
    Ritual *ptr_r = g.getBoard()->getRitual(pi);
    if (ptr_r) { // Replace Ritual
      delete g.getBoard()->getRitual(pi);
    }
    Ritual *ritualInHand = dynamic_cast<Ritual *>(hand.at(ci - 1));
    ptr_r = new Ritual(*ritualInHand);
    g.getBoard()->assignRitual(pi, ptr_r);
    discardCard(ci);
    return true;
  } else {
    return false;
  }
}

bool Player::placeMinion(unsigned int ci, unsigned int pi, Game &g) {
  // Actual Placing Minion
  int summoncost = hand.at(ci - 1)->getCost();
  if (useMP(summoncost)) {
    g.getBoard()->getMinions(pi).emplace_back(
        dynamic_cast<Minion *>(hand.at(ci - 1)));
    hand.erase(hand.begin() + ci - 1);

    // Trigger Standstill
    string r1name, r2name;

    if (g.getBoard()->getRitual(1))
      r1name = g.getBoard()->getRitual(1)->getName();
    if (g.getBoard()->getRitual(2))
      r2name = g.getBoard()->getRitual(2)->getName();
    // Standstill
    if (pi == 1) { // player1active
      if (r1name == "Standstill" &&
          g.getBoard()->getRitual(1)->processCostAndCharges()) {
        g.getBoard()->destoryNewMinion(1);
      } else if (r2name == "Standstill" &&
                 g.getBoard()->getRitual(2)->processCostAndCharges()) {
        g.getBoard()->destoryNewMinion(1);
      }
    } else {
      if (r1name == "Standstill" &&
          g.getBoard()->getRitual(1)->processCostAndCharges()) {
        g.getBoard()->destoryNewMinion(1);
      } else if (r2name == "Standstill" &&
                 g.getBoard()->getRitual(2)->processCostAndCharges()) {
        g.getBoard()->destoryNewMinion(1);
      }
    }
    return true;
  } else {
    return false;
  }
}

void Player::useSpell(unsigned int ci, unsigned int pi, unsigned int ti,
                      bool p1active, Game &g, bool testing) {
  string spellname = hand.at(ci - 1)->getName();
  int spellcost = hand.at(ci - 1)->getCost();
  if (spellname == "Banish") {
    if (!testing || mp <= spellcost) { // can't use act ability
      return;
    }
    if (mp >= spellcost) { // mp reduction
      upMP(-spellcost);
    }
    if (ti == 0) { // destroy ritual

      // case 1
      /*
      Ritual *ptr_r = g.getBoard()->getRitual(pi);
      delete g.getBoard()->getRitual(pi);
      ptr_r = nullptr;
      */
      // case 2
      g.getBoard()->removeRitual(pi);
    } else {                                          // destroy minion
      g.getBoard()->transferBoardToGraveyard(pi, ti); // send to graveyard
      g.notifyBoard(TriggerType::MLB);
    }
  } else if (spellname == "Unsummon") {
    if (!testing || mp <= spellcost) { // can't use act ability
      return;
    }
    if (mp >= spellcost) { // mp reduction
      upMP(-spellcost);
    }
    vector<Minion *> &minions = g.getBoard()->getMinions(pi);
    vector<Card *> &hand = g.getPlayer(pi)->getHand();
    hand.emplace_back(minions.at(ti - 1));
    minions.erase(minions.begin() + ti - 1);
  } else if (spellname == "Recharge") {
    if (!testing || mp <= spellcost) { // can't use act ability
      return;
    }
    if (mp >= spellcost) { // mp reduction
      upMP(-spellcost);
    }
    if (p1active) {
      g.getBoard()->getRitual(1)->upCharge(3);
    } else {
      g.getBoard()->getRitual(2)->upCharge(3);
    }
  } else if (spellname == "Disenchant") {
    if (!testing || mp <= spellcost) { // can't use act ability
      return;
    }
    if (mp >= spellcost) { // mp reduction
      upMP(-spellcost);
    }
    Minion *temp = g.getBoard()->getMinions(pi).at(ti - 1);
    g.getBoard()->getMinions(pi).at(ti - 1) =
        g.getBoard()->getMinions(pi).at(ti - 1)->getNext();
    temp->setNull();
    delete temp;
    //
  } else if (spellname == "Raise Dead") {
    if (!testing || mp <= spellcost) { // can't use act ability
      return;
    }
    if (mp >= spellcost) { // mp reduction
      upMP(-spellcost);
    }
    if (p1active) {
      g.getBoard()->transferGraveyardToBoard(1);
    } else {
      g.getBoard()->transferGraveyardToBoard(2);
    }
    g.notifyBoard(TriggerType::MEB);
  } else if (spellname == "Blizzard") {
    if (!testing || mp <= spellcost) { // can't use act ability
      return;
    }
    if (mp >= spellcost) { // mp reduction
      upMP(-spellcost);
    }
    vector<Minion *> &p1ms = g.getBoard()->getMinions(1);
    vector<Minion *> &p2ms = g.getBoard()->getMinions(2);
    if (p1active) {
      for (auto m1 : p1ms) {
        m1->addDef(-2);
      }
      g.processDeathMinions();
      for (auto m2 : p2ms) {
        m2->addDef(-2);
      }
      g.processDeathMinions();
    } else {
      for (auto m2 : p2ms) {
        m2->addDef(-2);
      }
      g.processDeathMinions();
      for (auto m1 : p1ms) {
        m1->addDef(-2);
      }
      g.processDeathMinions();
    }
  }
  g.processDeathMinions();
  discardCard(ci);
}

void Player::equipEnchantment(unsigned int ci, unsigned int pi, unsigned int ti,
                              Board *pbr) {
  Card *pc = hand.at(ci - 1);
  // Equipping Enchantment
  pbr->getMinions(pi).at(ti - 1) =
      new Enchantment(pc->getName(), pc->getDesc(), pc->getCost(),
                      pbr->getMinions(pi).at(ti - 1));
  int summoncost = pc->getCost();
  upMP(-summoncost);
  discardCard(ci); // destroy Enchantment Card in Hand
}
