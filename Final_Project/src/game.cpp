#include "game.h"

battle_ship::player *battle_ship::game::get_player(std::size_t p) {
  switch (p) {
  case 0:
    return player_1;
    break;

  default:
    return player_2;
    break;
  }
}