#include "vessel.h"
#include "board.h"
#include "geometry.h"
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
