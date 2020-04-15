#ifndef GEOM_H
#define GEOM_H
#include "coordinates.h"
#include <string>
namespace battle_ship {
class geometry {
public:
  static int orientation(coordinates p, coordinates q, coordinates r);
  static bool on_segment(coordinates p, coordinates q, coordinates r);
  static bool do_intersect(coordinates start_1, coordinates end_1,
                           coordinates start_2, coordinates end_2);
};
} // namespace battle_ship
#endif