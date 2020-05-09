#include "human.h"
#include "geometry.h"
#include "highscore_manager.h"
#include "market_manager.h"
#include "notification_manager.h"
#include "screen_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

void battle_ship::human::modify_fleet() {
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
        bool err;
        do {
          err = edit_piece();
        } while (err);
      } else {
        std::cout << "No pieces on board,sir." << std::endl;
      }
    } break;
    }
    if (budget == 0) {
      ready_to_play = true;
    } else {
      ready_to_play = false;
    }
    save_fleet();
  } while (input != 4);
  std::cout << "I will inform the troops,sir!" << std::endl;
}

bool battle_ship::human::add_piece() {
  std::cout << "These are the available pieces to be added. Please select one:"
            << std::endl;
  std::vector<std::string> available_pieces =
      battle_ship::market_manager::get_available_pieces(*this);
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
      battle_ship::market_manager::buy_piece(*this, order, coors, orientation);
  std::cout << std::get<1>(result);
  return std::get<0>(result);
}

bool battle_ship::human::remove_piece() {
  std::cout
      << "These are the available pieces to be removed. Please select one:"
      << std::endl;
  for (auto iterator = player_board->get_pieces().begin();
       iterator != player_board->get_pieces().end(); iterator++) {
    std::cout << (*iterator)->get_name() << std::endl;
  }
  std::cout << "Please enter the name of the piece you want:" << std::endl;
  std::cin.ignore();
  std::string order;
  std::cin >> order;
  std::tuple<bool, std::string> result =
      battle_ship::market_manager::sell_piece(*this, order);
  std::cout << std::get<1>(result);
  return std::get<0>(result);
}

bool battle_ship::human::edit_piece() {
  bool err{false};
  do {
    err = false;
    std::cout
        << "These are the available pieces to be edited. Please select one:"
        << std::endl;
    for (auto iterator = player_board->get_pieces().begin();
         iterator != player_board->get_pieces().end(); iterator++) {
      std::cout << (*iterator)->get_name() << std::endl;
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
    err = std::cin >> new_coor;
    if (err) {
      continue;
    }
    std::cout << "Please enter the orientation for the piece you want: "
                 "(v)ertical or (h)orizontal?"
              << std::endl;
    battle_ship::orientation new_orientation;
    std::string orientation_input;
    std::cin >> orientation_input;
    if (orientation_input == "v") {
      new_orientation = battle_ship::orientation::vertical;
    } else if (orientation_input == "h") {
      new_orientation = battle_ship::orientation::horizontal;
    } else {
      std::cout << "Please enter a valid orientation v or h.";
      err = true;
      continue;
    }

    bool found = false;
    size_t position_in_vector{0};
    for (auto iterator = player_board->get_pieces().begin();
         iterator != player_board->get_pieces().end(); iterator++) {
      if (piece_name == (*iterator)->get_name()) {
        player_board->edit_piece(**iterator, position_in_vector, new_coor,
                                 new_orientation);
        found = true;
        break;
      }
      position_in_vector += 1;
    }
    if (found) {
      err = false;
    } else {
      std::cout << "Unknown piece name.";
      err = true;
    }
  } while (err);
  std::cout << "Transaction successful.";
  return err;
}

void battle_ship::human::attack(battle_ship::piece &attacking_piece,
                                battle_ship::player &enemy) {
  for (size_t ap{}; ap < attacking_piece.get_action_points(); ap += 1) {
    battle_ship::coordinates target_coordinates;
    bool err{false};
    do {
      std::cout << "Please input the coordinates of the target:" << std::endl;
      err = std::cin >> target_coordinates;
      if (!err) {
        for (auto iterator = already_targeted.begin();
             iterator != already_targeted.end(); iterator++) {
          if (target_coordinates.col == (*iterator).col &&
              target_coordinates.row == (*iterator).row) {
            err = true;
            std::cout << "We have already hit this coordinate,sir."
                      << std::endl;
            break;
          }
        }
      }
    } while (err);
    already_targeted.push_back(target_coordinates);
    std::stringstream string_rep;
    string_rep << target_coordinates;
    notification_manager::add_notification(
        username, "Your " + attacking_piece.get_name() +
                      " sends a torpedo to " + string_rep.str());

    for (auto iterator = enemy.get_board().get_pieces().begin();
         iterator != enemy.get_board().get_pieces().end(); iterator++) {
      if (battle_ship::geometry::do_intersect(
              (*iterator)->get_start(), (*iterator)->get_end(),
              target_coordinates, target_coordinates)) {
        (*iterator)->take_hit();
        enemy.get_board().modify_coordinate(target_coordinates, "H");
        notification_manager::add_notification(
            username, "Well done, great hit commander!");
        if ((*iterator)->has_sunk()) {
          notification_manager::add_notification(
              username, "Enemy " + (*iterator)->get_name() + " has been sunk!");
        }
        return;
      }
    }
    enemy.get_board().modify_coordinate(target_coordinates, "M");
    notification_manager::add_notification(username, "Splash...Miss!");
  }
}

void battle_ship::human::save_highscore(size_t h) {
  highscore = h;
  battle_ship::highscore_manager::add_highscore(
      std::make_tuple(username, highscore));
  std::ofstream save_file;
  save_file.open("../saves/" + subdir + "/" + username + ".profile");
  save_file << password_hash << " " << highscore << std::endl;
  save_file.close();
};

void battle_ship::human::save_fleet() {
  std::ofstream fleet_configuration;
  fleet_configuration.open("../saves/" + subdir + "/" + username + ".fleet");
  auto output_orientation = [](battle_ship::orientation o) {
    return o == battle_ship::orientation::vertical ? "v" : "h";
  };

  for (auto iterator = player_board->get_pieces().begin();
       iterator != player_board->get_pieces().end(); iterator++) {
    fleet_configuration << (*iterator)->get_name() << " "
                        << (*iterator)->get_start() << " "
                        << output_orientation((*iterator)->get_orientation());
    if (iterator != player_board->get_pieces().end() - 1) {
      fleet_configuration << std::endl;
    }
  }
  fleet_configuration.close();
}

void battle_ship::human::winning_line() {
  std::cout << "Congratulations, commander! We have won the battle against "
            << enemy.lock()->get_uname() << "." << std::endl;
}