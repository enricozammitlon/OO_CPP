#ifndef GAME_H
#define GAME_H
#include "player.h"
namespace battle_ship {
/*!
 * \class game
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Holds the current battle state
 *
 * This class controls the logic of taking turns and holds
 * state about each player. Also holds the logic to check whether
 * end game conditions have been met
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Sat, 11 Apr 2020 09:49:03
 */
class game {
private:
  size_t whose_turn{0};
  std::shared_ptr<player> player_1;
  std::shared_ptr<player> player_2;

public:
  game() = default;
  game(size_t starting_turn, std::shared_ptr<player> p1,
       std::shared_ptr<player> p2)
      : whose_turn{starting_turn}, player_1{p1}, player_2{p2} {
    p1->assign_enemy(p2);
    p2->assign_enemy(p1);
  };
  player &get_player(size_t p);
  void toggle_turn() { whose_turn %= 1; };
  void play(std::shared_ptr<player> &winner);
  bool has_player_lost(player &p);
  ~game() = default;
};
} // namespace battle_ship
#endif