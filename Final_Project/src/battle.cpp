// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 26/03/2020
// Final Project : Battle Ship
// This is the main method to create the boards and initial configurations
// And actually play the game

#include "authentication.h"
#include "game.h"
#include "highscore_manager.h"
#include "human.h"
#include "notification_manager.h"
#include "npc.h"
#include "player.h"
#include "rules.h"
#include "screen_manager.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <tuple>
int main() {
  int input;
  std::shared_ptr<battle_ship::human> current_user = nullptr;
  do {
    std::cout << "Welcome to the Battleship registration! Please enter "
                 "one of the numbers below to start."
              << std::endl;
    std::cout << "[1] Sign up" << std::endl;
    std::cout << "[2] Sign in" << std::endl;
    std::cout << "[3] Exit" << std::endl;
    std::cin >> input;
    if (std::cin.fail() || input > 3 || input < 1) {
      std::cout << "Please enter a number 1-3." << std::endl;
      std::cin.clear();
      std::cin.ignore(512, '\n');
    }
    switch (input) {
    case 1:
      battle_ship::authentication::signup(current_user);
      break;
    case 2:
      battle_ship::authentication::signin(current_user);
      break;
    case 3:
      return 0;
    }
  } while (current_user == nullptr);

  std::unique_ptr<battle_ship::rules> standard_rules =
      std::make_unique<battle_ship::rules>();
  battle_ship::highscore_manager::initialise_highscores();
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
      std::shared_ptr<battle_ship::player> ai_1 =
          std::make_shared<battle_ship::npc>("Nemo", 1);
      battle_ship::notification_manager::reset_notifiations();
      std::unique_ptr<battle_ship::game> game_1 =
          std::make_unique<battle_ship::game>(0, current_user, ai_1,
                                              std::move(standard_rules));
      std::shared_ptr<battle_ship::player> winner{nullptr};
      game_1->play(winner);
      current_user->reset();
      if (winner == nullptr) {
        std::cout << "Please set up your fleet before playing." << std::endl;
        break;
      }
      winner->winning_line();
    } break;
    case 2: {
      current_user->modify_fleet();
    } break;
    case 3:
      std::cout << "These are the top 10 commanders of all time!" << std::endl;
      std::cout << "Commander" << std::setw(20) << "Turns" << std::endl;
      for (auto iterator =
               battle_ship::highscore_manager::all_highscores.begin();
           iterator != battle_ship::highscore_manager::all_highscores.end();
           iterator++) {
        std::cout << std::get<0>(*iterator)
                  << std::setw(
                         20 +
                         std::max(0, 9 - static_cast<int>(
                                             std::get<0>(*iterator).size())))
                  << std::get<1>(*iterator) << std::endl;
      }
      break;
    case 4:
      std::cout << "This program was made by Enrico Zammit Lonardelli for the "
                   "PHYS30762 course in Object Oriented C++."
                << std::endl;
      break;
    }
  } while (input != 5);
  return 0;
}
