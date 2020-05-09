#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "rules.h"
namespace battle_ship {
class game {
private:
  size_t whose_turn{0};
  std::shared_ptr<player> player_1;
  std::shared_ptr<player> player_2;
  std::unique_ptr<rules> current_rules;

public:
  game() = default;
  game(size_t starting_turn, std::shared_ptr<player> p1,
       std::shared_ptr<player> p2, std::unique_ptr<rules> r)
      : whose_turn{starting_turn}, player_1{p1}, player_2{p2},
        current_rules{std::move(r)} {
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