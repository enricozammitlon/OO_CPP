// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 26/03/2020
// Final Project : Battle Ship
// This is the main method to create the boards and initial configurations
// And actually play the game

#include "game.h"
#include "notification_manager.h"
#include "player.h"
#include "rules.h"
#include "screen_manager.h"
#include "sloop.h"
#include <iostream>

int main() {
  battle_ship::rules *standard_rules = new battle_ship::rules();
  battle_ship::player *human_1 = new battle_ship::player("Enrico");
  battle_ship::player *ai_1 = new battle_ship::player("Pericles");
  battle_ship::game *game_1 =
      new battle_ship::game(0, human_1, ai_1, standard_rules);
  /*
  battle_ship::coordinates p1{battle_ship::x_axis::J, 5};
  battle_ship::vessel *sloop_1 =
      new battle_ship::sloop(p1, battle_ship::orientation::vertical);
  *player_board << sloop_1;
  */
  battle_ship::screen_manager::side_by_side(game_1);
  // sloop_1->attack(player_board, computer_board);
  battle_ship::screen_manager::side_by_side(game_1);
  return 0;
}
