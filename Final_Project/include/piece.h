#ifndef PIECE_H
#define PIECE_H

#include "rules.h"
#include <string>
#include <vector>
namespace battle_ship {
class piece {
protected:
  std::string name;
  struct point start_point;
  struct point end_point;
  // Defined as distance on the x-axis
  std::size_t length;
  // Defined as distance on the y-axis
  std::size_t width;
  std::string xy_representation_horizontal;
  std::string xy_representation_vertical;
  std::string current_xy_representation;
  battle_ship::orientation orientation;
  std::size_t cost;
  std::string uri;
  bool *hit_points;

public:
  piece(std::string n, battle_ship::point p, std::size_t l, std::size_t w,
        std::string xy_rep_hor, std::string xy_rep_ver, std::string u,
        battle_ship::orientation o);
  std::vector<std::string> load_image(std::string name_of_file);
  std::string get_name() const { return name; };
  battle_ship::point get_start() const { return start_point; };
  battle_ship::point get_end() const { return end_point; };
  std::size_t get_length() const { return length; };
  std::size_t get_width() const { return width; };
  std::string get_uri() const { return uri; };
  std::string get_xy_representation() const {
    return current_xy_representation;
  };
  void hit(battle_ship::point pos) {
    size_t pos_x = size_t(pos.x_begin) - size_t(start_point.x_begin);
    size_t pos_y = pos.y_begin - start_point.y_begin;
    hit_points[pos_y + pos_x * width] = true;
  };
  virtual void display_yz() = 0;
  virtual void display_xy() = 0;
  virtual ~piece() { delete[] hit_points; };
};
} // namespace battle_ship
#endif