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
  orientation current_orientation;
  std::size_t cost;
  std::string uri;
  size_t hits{0};
  size_t action_points{0};

public:
  piece(std::string n, coordinates p, std::size_t l, std::size_t w,
        std::string xy_rep_hor, std::string xy_rep_ver, std::string u,
        orientation o, size_t a);
  piece(const piece &p);
  piece &operator=(const piece &p);
  piece(piece &&p);
  piece &operator=(piece &&p);
  std::vector<std::string> load_image(std::string name_of_file);
  std::string get_name() const { return name; };
  coordinates get_start() const { return start_coordinates; };
  coordinates get_end() const { return end_coordinates; };
  coordinates calculate_end(coordinates start, size_t distance, orientation o);
  void modify_pose(coordinates new_coors, orientation new_orientation);
  std::size_t get_length() const { return length; };
  std::size_t get_width() const { return width; };
  std::string get_uri() const { return uri; };
  std::size_t get_hits() const { return hits; };
  orientation get_orientation() const { return current_orientation; };
  bool has_sunk() const { return hits == (length * width); };
  std::string get_xy_representation() const {
    return current_xy_representation;
  };
  void take_hit() { hits += 1; };
  size_t get_action_points() { return action_points; };
  virtual void display_yz() = 0;
  virtual void display_xy() = 0;
  virtual ~piece() = default;
};
} // namespace battle_ship
#endif