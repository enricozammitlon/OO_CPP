#ifndef COORS_H
#define COORS_H
#include <iostream>
namespace battle_ship {
// Defines the x-axis
enum class x_axis {
  A = 1,
  B = 2,
  C = 3,
  D = 4,
  E = 5,
  F = 6,
  G = 7,
  H = 8,
  I = 9,
  J = 10
};
// Defines the possible orientations
enum class orientation { horizontal, vertical };
/*!
 * \struct coordinates
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Used to define points on a board
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Fri, 3 Apr 2020 17:34:54
 */
struct coordinates {
  friend std::ostream &operator<<(std::ostream &os, const coordinates &p);
  friend bool operator>>(std::istream &is, coordinates &p);
  x_axis col;
  size_t row;
  /** Used to increase the x-coordinate by a fixed amount
   * leaving the y-coordinate the same
   */
  coordinates boosted_x(size_t length) const;
  /** Used to increase the y-coordinate by a fixed amount
   * leaving the x-coordinate the same
   */
  coordinates boosted_y(size_t width) const;
};
} // namespace battle_ship
#endif