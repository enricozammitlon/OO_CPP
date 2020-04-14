#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "rules.h"
namespace battle_ship {
class game {
private:
  std::size_t whose_turn{0};
  std::shared_ptr<battle_ship::player> player_1;
  std::shared_ptr<battle_ship::player> player_2;
  std::unique_ptr<battle_ship::rules> rules;

public:
  game() = default;
  game(std::size_t starting_turn, std::shared_ptr<battle_ship::player> p1,
       std::shared_ptr<battle_ship::player> p2,
       std::unique_ptr<battle_ship::rules> r)
      : whose_turn{starting_turn}, player_1{p1}, player_2{p2}, rules{std::move(
                                                                   r)} {
    p1->assign_enemy(p2);
    p2->assign_enemy(p1);
  };
  battle_ship::player &get_player(std::size_t p);
  void toggle_turn() { whose_turn %= 1; };
  void play(std::shared_ptr<battle_ship::player> &winner);
  bool has_player_lost(battle_ship::player &p);
  ~game() = default;
};
} // namespace battle_ship
#endif