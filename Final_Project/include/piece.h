#ifndef PIECE_H
#define PIECE_H

#include "coordinates.h"
#include <string>
#include <vector>
namespace battle_ship {
/*!
 * \class piece
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Abstract/Interface for classes of type piece
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Sun, 29 Mar 2020 21:50:33
 */
class piece {

public:
  /// Given a start coordinate calculate the end coordinate
  virtual coordinates calculate_end(coordinates start, size_t distance,
                                    orientation o) = 0;
  /// Modifies position and orientation
  virtual void modify_pose(coordinates new_coors,
                           orientation new_orientation) = 0;
  virtual bool has_sunk() const = 0;
  virtual void take_hit() = 0;
  /// Displays what the top down view of this piece is
  virtual void display_xy() = 0;
  virtual size_t get_length() const = 0;
  virtual size_t get_width() const = 0;
  /// Returns the amount of hits already received from attacks
  virtual size_t get_hits() const = 0;
  virtual orientation get_orientation() const = 0;
  virtual std::string get_xy_representation() const = 0;
  virtual std::string get_name() const = 0;
  virtual int get_cost() const = 0;
  virtual coordinates get_start() const = 0;
  virtual coordinates get_end() const = 0;
  virtual size_t get_action_points() = 0;
  /// Needed since derived classes will call destructor at the end
  virtual ~piece(){};
};
} // namespace battle_ship
#endif