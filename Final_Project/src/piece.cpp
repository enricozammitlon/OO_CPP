#include "piece.h"
#include <fstream>
#include <iostream>
#include <vector>

battle_ship::piece::piece(std::string n, battle_ship::point p, std::size_t l,
                          std::size_t w, std::string xy_rep_hor,
                          std::string xy_rep_ver, std::string u,
                          battle_ship::orientation o) {
  name = n;
  start_point = {p.x_begin, p.y_begin};
  xy_representation_horizontal = xy_rep_hor;
  xy_representation_vertical = xy_rep_ver;
  orientation = o;
  uri = u;
  hit_points = new bool[l * w]();
  switch (o) {
  case (battle_ship::orientation::horizontal):
    length = l;
    width = w;
    current_xy_representation = xy_representation_horizontal;
    end_point = {
        static_cast<battle_ship::x_axis>(std::size_t(p.x_begin) + length - 1),
        p.y_begin};
    break;
  case (battle_ship::orientation::vertical):
    length = w;
    width = l;
    current_xy_representation = xy_representation_vertical;
    end_point = {p.x_begin, p.y_begin + width - 1};
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