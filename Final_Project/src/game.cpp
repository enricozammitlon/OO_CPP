#include "game.h"
#include "screen_manager.h"
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

void battle_ship::game::play() {
  if (!player_1->is_ready_to_play()) {
    std::cout << "Please set up your fleet before playing." << std::endl;
  }
  std::cout << "Playing..." << std::endl;
  battle_ship::screen_manager::side_by_side(this);
}