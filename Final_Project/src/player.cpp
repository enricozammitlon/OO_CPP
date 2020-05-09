#include "player.h"
#include "board.h"
#include "market_manager.h"
#include <fstream>
#include <string>
#include <tuple>

void battle_ship::player::reset() {
  already_targeted.clear();
  std::ifstream fleet_configuration;
  fleet_configuration.open("../saves/" + subdir + "/" + username + ".fleet");
  if (!fleet_configuration.good()) {
    player_board = std::make_unique<battle_ship::board>();
  } else {
    player_board = std::make_unique<battle_ship::board>();
    std::string order;
    battle_ship::coordinates coors;
    battle_ship::orientation orientation;
    while (!fleet_configuration.eof()) {
      std::string current_string;
      fleet_configuration >> order;
      fleet_configuration >> coors;
      fleet_configuration >> current_string;
      if (current_string == "v") {
        orientation = battle_ship::orientation::vertical;
      } else {
        orientation = battle_ship::orientation::horizontal;
      }
      if (fleet_configuration.fail()) {
        fleet_configuration.clear();
        fleet_configuration.ignore(512, '\n');
        continue;
      }
      // Although there is a returned transaction success here, this is
      // guaranteed to work because when it was saved the first time this state
      // was checked elsewhere in the code (The edit fleet screen).
      battle_ship::market_manager::buy_piece(*this, order, coors, orientation);
    }
    fleet_configuration.close();
  }
  if (budget == 0) {
    ready_to_play = true;
  } else {
    ready_to_play = false;
  }
}
