#ifndef VESSEL_H
#define VESSEL_H

#include "board.h"
#include "piece.h"
#include <iostream>
#include <string>

namespace battle_ship {
/*!
 * \class vessel
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Implements the methods for the abstract piece class
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Sun, 29 Mar 2020 21:50:33
 */
class vessel : public piece {
protected:
  std::string name;
  struct coordinates start_coordinates;
  struct coordinates end_coordinates;
  /// Defined as distance on the x-axis
  size_t length;
  /// Defined as distance on the y-axis
  size_t width;
  std::string xy_representation_horizontal;
  std::string xy_representation_vertical;
  std::string current_xy_representation;
  orientation current_orientation;
  int cost{100};
  size_t hits{0};
  /// The number of turns this piece allows a player to attack if using it
  size_t action_points{0};

public:
  vessel() = default;
  vessel(std::string n, coordinates p, size_t l, size_t w,
         std::string xy_rep_hor, std::string xy_rep_ver, orientation o,
         size_t ap);
  coordinates calculate_end(coordinates start, size_t distance,
                            orientation o) override;
  void modify_pose(coordinates new_coors, orientation new_orientation) override;
  bool has_sunk() const override { return hits == (length * width); };
  void take_hit() override { hits += 1; };
  void display_xy() override;
  size_t get_action_points() override { return action_points; };
  size_t get_length() const override { return length; };
  size_t get_width() const override { return width; };
  size_t get_hits() const override { return hits; };
  std::string get_xy_representation() const override {
    return current_xy_representation;
  };
  orientation get_orientation() const override { return current_orientation; };
  std::string get_name() const override { return name; };
  coordinates get_start() const override { return start_coordinates; };
  coordinates get_end() const override { return end_coordinates; };
  int get_cost() const override { return cost; };
  virtual ~vessel() = default;
};
} // namespace battle_ship
#endif