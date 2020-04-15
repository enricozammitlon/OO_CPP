#include "piece.h"
#include <fstream>
#include <iostream>
#include <vector>

battle_ship::piece::piece(std::string n, battle_ship::coordinates p,
                          std::size_t l, std::size_t w, std::string xy_rep_hor,
                          std::string xy_rep_ver, std::string u,
                          battle_ship::orientation o, size_t a) {
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
battle_ship::piece::calculate_end(battle_ship::coordinates start,
                                  size_t distance, battle_ship::orientation o) {
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

battle_ship::piece::piece(const piece &p) {
  name = p.name;
  start_coordinates = p.start_coordinates;
  end_coordinates = p.end_coordinates;
  length = p.length;
  width = p.width;
  xy_representation_horizontal = p.xy_representation_horizontal;
  xy_representation_vertical = p.xy_representation_vertical;
  current_xy_representation = p.current_xy_representation;
  current_orientation = p.current_orientation;
  cost = p.cost;
  uri = p.uri;
  hits = p.hits;
}

battle_ship::piece &battle_ship::piece::operator=(const piece &p) {
  if (&p == this)
    return *this;
  name = p.name;
  start_coordinates = p.start_coordinates;
  end_coordinates = p.end_coordinates;
  length = p.length;
  width = p.width;
  xy_representation_horizontal = p.xy_representation_horizontal;
  xy_representation_vertical = p.xy_representation_vertical;
  current_xy_representation = p.current_xy_representation;
  current_orientation = p.current_orientation;
  cost = p.cost;
  uri = p.uri;
  hits = p.hits;
  return *this;
}

battle_ship::piece::piece(piece &&p) {
  name = p.name;
  start_coordinates = p.start_coordinates;
  end_coordinates = p.end_coordinates;
  length = p.length;
  width = p.width;
  xy_representation_horizontal = p.xy_representation_horizontal;
  xy_representation_vertical = p.xy_representation_vertical;
  current_xy_representation = p.current_xy_representation;
  current_orientation = p.current_orientation;
  cost = p.cost;
  uri = p.uri;
  hits = p.hits;
  p.name = "";
  p.start_coordinates = {battle_ship::x_axis::A, 1};
  p.end_coordinates = {battle_ship::x_axis::A, 1};
  p.length = 0;
  p.width = 0;
  p.xy_representation_horizontal = "";
  p.xy_representation_vertical = "";
  p.current_xy_representation = "";
  p.current_orientation = battle_ship::orientation::vertical;
  p.cost = 0;
  p.uri = "";
  p.hits = 0;
}

battle_ship::piece &battle_ship::piece::operator=(piece &&p) {
  std::swap(name, p.name);
  std::swap(start_coordinates, p.start_coordinates);
  std::swap(end_coordinates, p.end_coordinates);
  std::swap(length, p.length);
  std::swap(width, p.width);
  std::swap(xy_representation_horizontal, p.xy_representation_horizontal);
  std::swap(xy_representation_vertical, p.xy_representation_vertical);
  std::swap(current_xy_representation, p.current_xy_representation);
  std::swap(current_orientation, p.current_orientation);
  std::swap(cost, p.cost);
  std::swap(uri, p.uri);
  std::swap(hits, p.hits);
  return *this;
}

void battle_ship::piece::modify_pose(battle_ship::coordinates new_coors,
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

std::vector<std::string>
battle_ship::piece::load_image(std::string name_of_file) {
  std::ifstream image_file;
  image_file.open(name_of_file);
  if (!image_file.good()) {
    std::string err = "Error: File " + name_of_file + " could not be opened.";
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