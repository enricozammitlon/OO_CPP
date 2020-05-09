#include "npc.h"
#include "geometry.h"
#include "notification_manager.h"
#include "piece.h"
#include "player.h"
#include <cstdlib>
#include <iostream>

void battle_ship::npc::winning_line() {
  std::cout << "Commander...*cough*...we've been defated by " << username << "."
            << std::endl;
}
void battle_ship::npc::attack(battle_ship::piece &attacking_piece,
                              battle_ship::player &enemy) {
  for (size_t ap{}; ap < attacking_piece.get_action_points(); ap += 1) {
    bool err{false};
    battle_ship::coordinates target_coordinates;
    do {
      err = false;
      battle_ship::x_axis random_x =
          static_cast<battle_ship::x_axis>((rand() % 9) + 1);
      size_t random_y = (rand() % 9) + 1;
      target_coordinates.col = random_x;
      target_coordinates.row = random_y;
      for (auto iterator = already_targeted.begin();
           iterator != already_targeted.end(); iterator++) {
        if (target_coordinates.col == (*iterator).col &&
            target_coordinates.row == (*iterator).row) {
          err = true;
          break;
        }
      }
    } while (err);
    already_targeted.push_back(target_coordinates);
    std::stringstream string_rep;
    string_rep << target_coordinates;
    notification_manager::add_notification(
        username, "The enemy's " + attacking_piece.get_name() +
                      " sends a torpedo to " + string_rep.str());

    for (auto iterator = enemy.get_board().get_pieces().begin();
         iterator != enemy.get_board().get_pieces().end(); iterator++) {
      if (battle_ship::geometry::do_intersect(
              (*iterator)->get_start(), (*iterator)->get_end(),
              target_coordinates, target_coordinates)) {
        (*iterator)->take_hit();
        enemy.get_board().modify_coordinate(target_coordinates, "H");
        notification_manager::add_notification(username,
                                               "The enemy has hit us!");
        if ((*iterator)->has_sunk()) {
          notification_manager::add_notification(
              username, "Our " + (*iterator)->get_name() + " has been sunk!");
        }
        return;
      }
    }
    enemy.get_board().modify_coordinate(target_coordinates, "M");
    notification_manager::add_notification(username, "The enemy has missed!");
  }
};
