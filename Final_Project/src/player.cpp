#include "player.h"
#include "market.h"
#include "screen_manager.h"
#include <iostream>
#include <tuple>

void battle_ship::player::modify_fleet() {
  std::cout << "Commander, this is your configuration editor. Please follow "
               "instructions to edit your fleet positioning."
            << std::endl;
  int input;
  do {
    std::cout << "This is your current configuration." << std::endl;
    std::cout << *player_board;
    std::cout << "Enter one of the numbers below to execute that order."
              << std::endl;
    std::cout << "[1] Add piece" << std::endl;
    std::cout << "[2] Remove Piece" << std::endl;
    std::cout << "[3] Change position of piece" << std::endl;
    std::cout << "[4] To main menu" << std::endl;
    std::cin >> input;
    if (std::cin.fail() || input > 4 || input < 1) {
      std::cout << "Please enter a number 1-4." << std::endl;
      std::cin.clear();
      std::cin.ignore(512, '\n');
    }
    switch (input) {
    case 1: {
      if (budget > 0) {
        bool result;
        do {
          result = add_piece();
        } while (!result);
      } else {
        std::cout << "I am afraid we are out of money,sir." << std::endl;
      }
    } break;
    case 2: {
      if (player_board->get_pieces().size() > 0) {
        bool result;
        do {
          result = remove_piece();
        } while (!result);
      } else {
        std::cout << "No pieces on board,sir." << std::endl;
      }
    } break;
    case 3: {
      if (player_board->get_pieces().size() > 0) {
        bool result;
        do {
          result = edit_piece();
        } while (!result);
      } else {
        std::cout << "No pieces on board,sir." << std::endl;
      }
    } break;
    }
    if (budget = 0) {
      ready_to_play = true;
    } else {
      ready_to_play = false;
    }
  } while (input != 4);
  std::cout << "I will inform the troops,sir!" << std::endl;
}

bool battle_ship::player::add_piece() {
  std::cout << "These are the available pieces to be added. Please select one:"
            << std::endl;
  std::vector<std::string> available_pieces =
      battle_ship::market::get_available_pieces(this);
  for (auto iterator = available_pieces.begin();
       iterator != available_pieces.end(); iterator++) {
    std::cout << *iterator << std::endl;
  }
  std::cout << "Please enter the name of the piece you want:" << std::endl;
  std::cin.ignore();
  std::string order;
  std::cin >> order;
  std::cout << "Please enter the start coordinate of where you want the "
               "piece to be:"
            << std::endl;
  std::cin.ignore();
  battle_ship::coordinates coors;
  std::cin >> coors;
  std::cout << "Please enter the orientation for the piece you want: "
               "(v)ertical or (h)orizontal?"
            << std::endl;
  battle_ship::orientation orientation;
  std::string orientation_input;
  std::cin >> orientation_input;
  if (orientation_input == "v") {
    orientation = battle_ship::orientation::vertical;
  } else {
    orientation = battle_ship::orientation::horizontal;
  }
  std::tuple<bool, std::string> result =
      battle_ship::market::buy_piece(this, order, coors, orientation);
  std::cout << std::get<1>(result);
  return std::get<0>(result);
}

bool battle_ship::player::remove_piece() {
  std::cout
      << "These are the available pieces to be removed. Please select one:"
      << std::endl;
  std::vector<battle_ship::piece *> all_pieces = player_board->get_pieces();
  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    battle_ship::piece *current_piece = *iterator;
    std::cout << current_piece->get_name() << std::endl;
  }
  std::cout << "Please enter the name of the piece you want:" << std::endl;
  std::cin.ignore();
  std::string order;
  std::cin >> order;
  std::tuple<bool, std::string> result =
      battle_ship::market::sell_piece(this, order);
  std::cout << std::get<1>(result);
  return std::get<0>(result);
}

bool battle_ship::player::edit_piece() {
  std::cout << "These are the available pieces to be edited. Please select one:"
            << std::endl;
  std::vector<battle_ship::piece *> all_pieces = player_board->get_pieces();
  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    battle_ship::piece *current_piece = *iterator;
    std::cout << current_piece->get_name() << std::endl;
  }
  std::cout << "Please enter the name of the piece you want:" << std::endl;
  std::cin.ignore();
  std::string piece_name;
  std::cin >> piece_name;
  std::cout << "Please enter the start coordinate of where you want the "
               "piece to be:"
            << std::endl;
  std::cin.ignore();
  battle_ship::coordinates new_coor;
  std::cin >> new_coor;
  std::cout << "Please enter the orientation for the piece you want: "
               "(v)ertical or (h)orizontal?"
            << std::endl;
  battle_ship::orientation new_orientation;
  std::string orientation_input;
  std::cin >> orientation_input;
  if (orientation_input == "v") {
    new_orientation = battle_ship::orientation::vertical;
  } else {
    new_orientation = battle_ship::orientation::horizontal;
  }

  battle_ship::piece *element_to_edit;
  bool found = false;
  size_t position_in_vector{0};
  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    if (piece_name == (*iterator)->get_name()) {
      element_to_edit = *iterator;
      found = true;
      break;
    }
    position_in_vector += 1;
  }
  if (found) {
    player_board->edit_piece(element_to_edit, position_in_vector, new_coor,
                             new_orientation);
    std::cout << "Transaction successful.";
    return true;
  } else {
    std::cout << "Unknown piece name.";
    return false;
  }
}