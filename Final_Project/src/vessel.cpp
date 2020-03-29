#include "vessel.h"
#include "board.h"
#include "rules.h"
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
    battle_ship::point target_point;
    std::cin >> target_point;
    bool result = enemy_board->take_hit(target_point);
    if (result) {
      std::cout << "Well done, great hit commander!" << std::endl;
    } else {
      std::cout << "Miss!" << std::endl;
    }
  }
}