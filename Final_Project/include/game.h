#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "rules.h"
namespace battle_ship {
class game {
private:
  std::size_t current_turn{0};
  battle_ship::player *player_1;
  battle_ship::player *player_2;
  battle_ship::rules *rules;

public:
  game() = default;
  game(std::size_t starting_turn, battle_ship::player *p1,
       battle_ship::player *p2, battle_ship::rules *r)
      : current_turn{starting_turn}, player_1{p1}, player_2{p2}, rules{r} {};
  battle_ship::player *get_player(std::size_t p);
  void toggle_turn() { current_turn = current_turn % 1; };
  ~game() = default;
};
} // namespace battle_ship
#endif