#ifndef GEOM_H
#define GEOM_H
#include "coordinates.h"
#include <string>
namespace battle_ship {
class geometry {
public:
  static int orientation(battle_ship::coordinates p, battle_ship::coordinates q,
                         battle_ship::coordinates r);
  static bool on_segment(battle_ship::coordinates p, battle_ship::coordinates q,
                         battle_ship::coordinates r);
  static bool do_intersect(battle_ship::coordinates start_1,
                           battle_ship::coordinates end_1,
                           battle_ship::coordinates start_2,
                           battle_ship::coordinates end_2);
};
} // namespace battle_ship
#endif