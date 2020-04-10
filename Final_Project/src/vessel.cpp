#include "../include/vessel.h"
#include "../include/board.h"
#include "../include/rules.h"
#include "notification_manager.h"
#include <iostream>
#include <string>
#include <vector>
void battle_ship::vessel::display_yz() {
  std::vector<std::string> all_lines = battle_ship::piece::load_image(uri);
  for (auto iterator = all_lines.begin(); iterator != all_lines.end();
       iterator++) {
    std::cout << *iterator << std::endl;
  };
}
void battle_ship::vessel::display_xy() {
  std::cout << current_xy_representation << std::endl;
}

void battle_ship::vessel::attack(battle_ship::board *enemy_board) {
  for (size_t ap{}; ap < action_points; ap += 1) {
    std::cout << "Please input the coordinates of the target:" << std::endl;
    battle_ship::coordinates target_coordinates;
    std::cin >> target_coordinates;
    bool result = enemy_board->receive_attempt_hit(target_coordinates);
    if (result) {
      notification_manager::add_notification("Well done, great hit commander!");
    } else {
      notification_manager::add_notification("Miss!");
    }
  }
}