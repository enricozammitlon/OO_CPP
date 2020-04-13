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
  battle_ship::player *current_user = new battle_ship::player("Enrico");

  int input;
  do {
    std::cout << "Welcome to your Battleship terminal commander! Please enter "
                 "one of the numbers below to start."
              << std::endl;
    std::cout << "[1] New Game" << std::endl;
    std::cout << "[2] Your Fleet" << std::endl;
    std::cout << "[3] Highscores" << std::endl;
    std::cout << "[4] Credits" << std::endl;
    std::cout << "[5] Exit" << std::endl;
    std::cin >> input;
    if (std::cin.fail() || input > 5 || input < 1) {
      std::cout << "Please enter a number 1-5." << std::endl;
      std::cin.clear();
      std::cin.ignore(512, '\n');
    }
    switch (input) {
    case 1: {
      battle_ship::player *ai_1 = new battle_ship::player("Pericles");
      battle_ship::game *game_1 =
          new battle_ship::game(0, current_user, ai_1, standard_rules);
      game_1->play();

    } break;
    case 2: {
      current_user->modify_fleet();
    } break;
    case 3:
      std::cout << "Highscores here..." << std::endl;
      break;
    case 4:
      std::cout << "Credits here..." << std::endl;
      break;
    }
  } while (input != 5);
  /*
  battle_ship::coordinates p1{battle_ship::x_axis::J, 5};
  battle_ship::vessel *sloop_1 =
      new battle_ship::sloop(p1, battle_ship::orientation::vertical);
  *player_board << sloop_1;
  */

  // sloop_1->attack(player_board, computer_board);
  return 0;
}
