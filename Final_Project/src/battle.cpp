// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 26/03/2020
// Final Project : Battle Ship
// This is the main method to create the boards and initial configurations
// And actually play the game

#include "board.h"
#include "notification_manager.h"
#include "rules.h"
#include "screen_manager.h"
#include "sloop.h"
#include <iostream>

int main() {
  const size_t board_size_x{10};
  const size_t board_size_y{10};
  battle_ship::board *player_board =
      new battle_ship::board(board_size_x, board_size_y);
  battle_ship::board *computer_board =
      new battle_ship::board(board_size_x, board_size_y);

  battle_ship::coordinates p1{battle_ship::x_axis::J, 5};
  battle_ship::vessel *sloop_1 =
      new battle_ship::sloop(p1, battle_ship::orientation::vertical);
  *player_board << sloop_1;

  battle_ship::coordinates p2{battle_ship::x_axis::E, 7};
  battle_ship::vessel *sloop_2 =
      new battle_ship::sloop(p2, battle_ship::orientation::horizontal);
  *player_board << sloop_2;

  battle_ship::coordinates p3{battle_ship::x_axis::B, 1};
  battle_ship::vessel *sloop_3 =
      new battle_ship::sloop(p3, battle_ship::orientation::horizontal);
  *computer_board << sloop_3;

  battle_ship::coordinates p4{battle_ship::x_axis::F, 7};
  battle_ship::vessel *sloop_4 =
      new battle_ship::sloop(p4, battle_ship::orientation::vertical);
  *computer_board << sloop_4;

  battle_ship::screen_manager::side_by_side(*player_board, *computer_board, 5);
  // sloop_1->display_yz();
  sloop_1->attack(computer_board);
  battle_ship::screen_manager::side_by_side(*player_board, *computer_board, 5);
  return 0;
}
