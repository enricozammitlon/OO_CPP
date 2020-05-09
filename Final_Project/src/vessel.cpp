#include "vessel.h"
#include "board.h"
#include "geometry.h"
#include "notification_manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

battle_ship::vessel::vessel(std::string n, battle_ship::coordinates p, size_t l,
                            size_t w, std::string xy_rep_hor,
                            std::string xy_rep_ver, battle_ship::orientation o,
                            std::string u, size_t a) {
  name = n;
  start_coordinates = {p.col, p.row};
  xy_representation_horizontal = xy_rep_hor;
  xy_representation_vertical = xy_rep_ver;
  current_orientation = o;
  uri = u;
  action_points = a;
  switch (o) {
  case (battle_ship::orientation::horizontal):
    length = l;
    width = w;
    current_xy_representation = xy_representation_horizontal;
    end_coordinates =
        calculate_end(start_coordinates, length, current_orientation);
    break;
  case (battle_ship::orientation::vertical):
    length = w;
    width = l;
    current_xy_representation = xy_representation_vertical;
    end_coordinates =
        calculate_end(start_coordinates, width, current_orientation);
    break;
  }
};

battle_ship::coordinates
battle_ship::vessel::calculate_end(battle_ship::coordinates start,
                                   size_t distance,
                                   battle_ship::orientation o) {
  switch (o) {
  case (battle_ship::orientation::horizontal):
    return start_coordinates.boosted_x(distance - 1);
    break;
  case (battle_ship::orientation::vertical):
    return start_coordinates.boosted_y(distance - 1);
    break;
  default:
    return start_coordinates;
    break;
  }
};

void battle_ship::vessel::modify_pose(
    battle_ship::coordinates new_coors,
    battle_ship::orientation new_orientation) {
  start_coordinates = new_coors;
  if (new_orientation != current_orientation) {
    size_t old_length = length;
    length = width;
    width = old_length;
  }
  current_orientation = new_orientation;
  switch (new_orientation) {
  case (battle_ship::orientation::horizontal):
    current_xy_representation = xy_representation_horizontal;
    end_coordinates =
        calculate_end(start_coordinates, length, current_orientation);
    break;
  case (battle_ship::orientation::vertical):
    current_xy_representation = xy_representation_vertical;
    end_coordinates =
        calculate_end(start_coordinates, width, current_orientation);
    break;
  }
};

std::vector<std::string> battle_ship::vessel::load_image() const {
  std::ifstream image_file;
  image_file.open(uri);
  if (!image_file.good()) {
    std::string err = "Error: File " + uri + " could not be opened.";
    std::cout << err;
  }
  std::vector<std::string> all_lines;
  size_t number_of_read_values{0};
  while (!image_file.eof()) {
    std::string current_line{};
    std::getline(image_file, current_line);
    all_lines.push_back(current_line);
    if (image_file.fail()) {
      image_file.clear();
      image_file.ignore(512, '\n');
      std::cout << "Warning: Error at line ";
      std::cout << (number_of_read_values + 1) << std::endl;
      continue;
    }
    number_of_read_values += 1;
  }
  image_file.close();
  return all_lines;
}

void battle_ship::vessel::display_yz() {
  std::vector<std::string> all_lines = load_image();
  for (auto iterator = all_lines.begin(); iterator != all_lines.end();
       iterator++) {
    std::cout << *iterator << std::endl;
  };
}

void battle_ship::vessel::display_xy() {
  std::cout << current_xy_representation << std::endl;
}