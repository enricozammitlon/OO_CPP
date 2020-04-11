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

void battle_ship::vessel::attack(battle_ship::board *player_board,
                                 battle_ship::board *enemy_board) {
  for (size_t ap{}; ap < action_points; ap += 1) {
    std::cout << "Please input the coordinates of the target:" << std::endl;
    battle_ship::coordinates target_coordinates;
    std::cin >> target_coordinates;
    bool result{false};
    std::vector<battle_ship::piece *> enemy_pieces = enemy_board->get_pieces();

    for (auto iterator = enemy_pieces.begin(); iterator != enemy_pieces.end();
         iterator++) {
      battle_ship::piece *current_piece = *iterator;

      if (battle_ship::geometry::do_intersect(
              current_piece->get_start(), current_piece->get_end(),
              target_coordinates, target_coordinates)) {
        current_piece->take_hit(target_coordinates);
        result = true;
        break;
      }
    }
    if (result) {
      enemy_board->modify_coordinate(target_coordinates, "H");
      notification_manager::add_notification("Well done, great hit commander!");
    } else {
      enemy_board->modify_coordinate(target_coordinates, "M");
      notification_manager::add_notification("Miss!");
    }
  }
}