#ifndef RULES_H
#define RULES_H
#include "coordinates.h"
#include <string>
namespace battle_ship {
class rules {
public:
  static std::string current_turn;
  static int orientation(battle_ship::coordinates p, battle_ship::coordinates q,
                         battle_ship::coordinates r);
  static bool on_segment(battle_ship::coordinates p, battle_ship::coordinates q,
                         battle_ship::coordinates r);
  static bool do_intersect(battle_ship::coordinates start_1,
                           battle_ship::coordinates end_1,
                           battle_ship::coordinates start_2,
                           battle_ship::coordinates end_2);
  static const std::size_t initial_budget{1000};
};
} // namespace battle_ship
#endif