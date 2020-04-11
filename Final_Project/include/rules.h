#ifndef RULES_H
#define RULES_H
#include "player.h"
#include <string>
namespace battle_ship {
class rules {
private:
  std::string current_turn{0};
  std::size_t initial_budget{1000};
  bool has_player_lost(battle_ship::player p);

public:
  rules() = default;
  rules(std::string starting_p, std::size_t init_budget)
      : current_turn{starting_p}, initial_budget{init_budget} {};
};
} // namespace battle_ship
#endif