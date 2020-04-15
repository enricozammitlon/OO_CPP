#include "player.h"
#include "market.h"
#include <fstream>
#include <string>
#include <tuple>

void battle_ship::player::reset() {
  budget = 100;
  already_targeted.clear();
  std::ifstream fleet_configuration;
  fleet_configuration.open("../saves/" + subdir + "/" + username + ".fleet");
  if (!fleet_configuration.good()) {
    player_board = std::make_unique<battle_ship::board>();
  } else {
    player_board = std::make_unique<battle_ship::board>();
    size_t counter{0};
    std::string order;
    battle_ship::coordinates coors;
    battle_ship::orientation orientation;
    while (!fleet_configuration.eof()) {
      counter += 1;
      std::string current_string;
      if (counter == 1) {
        fleet_configuration >> order;
      } else if (counter == 2) {
        fleet_configuration >> coors;
      } else if (counter == 3) {
        fleet_configuration >> current_string;
        if (current_string == "v") {
          orientation = battle_ship::orientation::vertical;
        } else {
          orientation = battle_ship::orientation::horizontal;
        }
      } else {
        fleet_configuration >> current_string;
      }
      if (fleet_configuration.fail()) {
        fleet_configuration.clear();
        fleet_configuration.ignore(512, '\n');
        continue;
      }
    }
    std::tuple<bool, std::string> result =
        battle_ship::market::buy_piece(*this, order, coors, orientation);
    fleet_configuration.close();
  }
  if (budget == 0) {
    ready_to_play = true;
  } else {
    ready_to_play = false;
  }
}
