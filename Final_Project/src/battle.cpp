// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 26/03/2020
// Final Project : Battle Ship
// This is the main method to create the boards and initial configurations
// And actually play the game

#include "board.h"
#include "rules.h"
#include "sloop.h"
#include <iostream>
int main() {
  const size_t board_size_x{10};
  const size_t board_size_y{10};
  battle_ship::board *player_board =
      new battle_ship::board(board_size_x, board_size_y);
  battle_ship::board *computer_board =
      new battle_ship::board(board_size_x, board_size_y);

  struct battle_ship::point p1 {
    battle_ship::x_axis::J, 5
  };
  battle_ship::vessel *sloop_1 =
      new battle_ship::sloop(p1, battle_ship::orientation::vertical);
  *player_board << sloop_1;

  struct battle_ship::point p2 {
    battle_ship::x_axis::E, 7
  };
  battle_ship::vessel *sloop_2 =
      new battle_ship::sloop(p2, battle_ship::orientation::horizontal);
  *player_board << sloop_2;

  std::cout << *player_board;
  sloop_1->display_yz();
  sloop_1->attack(player_board);
  std::cout << *player_board;
  return 0;
}
