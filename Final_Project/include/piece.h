#ifndef PIECE_H
#define PIECE_H

#include "coordinates.h"
#include <string>
#include <vector>
namespace battle_ship {
class piece {
protected:
  std::string name;
  struct coordinates start_coordinates;
  struct coordinates end_coordinates;
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
  bool *hit_coordinates;

public:
  piece(std::string n, battle_ship::coordinates p, std::size_t l, std::size_t w,
        std::string xy_rep_hor, std::string xy_rep_ver, std::string u,
        battle_ship::orientation o);
  piece(const piece &arr);
  piece &operator=(const piece &arr);
  piece(piece &&arr);
  piece &operator=(piece &&arr);
  std::vector<std::string> load_image(std::string name_of_file);
  std::string get_name() const { return name; };
  battle_ship::coordinates get_start() const { return start_coordinates; };
  battle_ship::coordinates get_end() const { return end_coordinates; };
  battle_ship::coordinates calculate_end(battle_ship::coordinates start,
                                         size_t distance,
                                         battle_ship::orientation o);
  void modify_pose(battle_ship::coordinates new_coors,
                   battle_ship::orientation new_orientation);
  std::size_t get_length() const { return length; };
  std::size_t get_width() const { return width; };
  std::string get_uri() const { return uri; };
  std::string get_xy_representation() const {
    return current_xy_representation;
  };
  void take_hit(battle_ship::coordinates target_coordinate) {
    size_t pos_x =
        size_t(target_coordinate.col) - size_t(start_coordinates.col);
    size_t pos_y = target_coordinate.row - start_coordinates.row;
    hit_coordinates[pos_x + pos_y * length] = true;
  };
  virtual void display_yz() = 0;
  virtual void display_xy() = 0;
  virtual ~piece() { delete[] hit_coordinates; };
};
} // namespace battle_ship
#endif