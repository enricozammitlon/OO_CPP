#ifndef GEOM_H
#define GEOM_H
#include "coordinates.h"
#include <string>
namespace battle_ship {
/*!
 * \class geometry
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Used to hold geometrical algorithms
 *
 * This class is used to check if two line segments
 * intersect. Practically used to check if two pieces intersect
 * and if a target coordinate hits a piece.
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Sat, 11 Apr 2020 09:49:03
 */
class geometry {
public:
  static int orientation(coordinates p, coordinates q, coordinates r);
  static bool on_segment(coordinates p, coordinates q, coordinates r);
  static bool do_intersect(coordinates start_1, coordinates end_1,
                           coordinates start_2, coordinates end_2);
};
} // namespace battle_ship
#endif