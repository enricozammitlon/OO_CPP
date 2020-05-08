#ifndef PIECE_H
#define PIECE_H

#include "coordinates.h"
#include <string>
#include <vector>
namespace battle_ship {
class piece {

public:
  virtual std::vector<std::string> load_image() const = 0;
  virtual coordinates calculate_end(coordinates start, size_t distance,
                                    orientation o) = 0;
  virtual void modify_pose(coordinates new_coors,
                           orientation new_orientation) = 0;
  virtual bool has_sunk() const = 0;
  virtual void take_hit() = 0;
  virtual void display_yz() = 0;
  virtual void display_xy() = 0;
  virtual std::size_t get_length() const = 0;
  virtual std::size_t get_width() const = 0;
  virtual std::string get_uri() const = 0;
  virtual std::size_t get_hits() const = 0;
  virtual orientation get_orientation() const = 0;
  virtual std::string get_xy_representation() const = 0;
  virtual std::string get_name() const = 0;
  virtual int get_cost() const = 0;
  virtual coordinates get_start() const = 0;
  virtual coordinates get_end() const = 0;
  virtual size_t get_action_points() = 0;
};
} // namespace battle_ship
#endif