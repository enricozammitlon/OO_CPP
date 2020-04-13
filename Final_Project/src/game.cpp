#include "game.h"
#include "screen_manager.h"
#include "vessel.h"
#include <iterator>
#include <vector>
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

battle_ship::player *battle_ship::game::play() {
  battle_ship::player *winner = nullptr;
  if (!player_1->is_ready_to_play()) {
    return winner;
  }
  battle_ship::player *current_player = nullptr;
  battle_ship::screen_manager::side_by_side(this);
  do {
    if (current_player == player_1) {
      current_player = player_2;
    } else {
      current_player = player_1;
    }
    battle_ship::piece *attacking_piece;
    std::vector<battle_ship::piece *> all_pieces =
        current_player->get_board().get_pieces();
    for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
         iterator++) {
      if (!(*iterator)->has_sunk()) {
        attacking_piece = *iterator;
        break;
      }
    }
    current_player->attack(attacking_piece, current_player->get_enemy());
    if (has_player_lost(current_player->get_enemy())) {
      winner = current_player;
    }
    battle_ship::screen_manager::side_by_side(this);
  } while (winner == nullptr);
  return winner;
}

bool battle_ship::game::has_player_lost(battle_ship::player *p) {
  size_t sunken_counter{0};
  std::vector<battle_ship::piece *> all_pieces = p->get_board().get_pieces();
  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    if ((*iterator)->has_sunk()) {
      sunken_counter += 1;
    }
  }
  if (sunken_counter == all_pieces.size()) {
    return true;
  } else {
    return false;
  }
}
