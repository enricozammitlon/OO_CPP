#ifndef CRUISER_H
#define CRUISER_H

#include "rules.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
class missile_cruiser : public vessel {

public:
  missile_cruiser() = default;
  missile_cruiser(battle_ship::point p, battle_ship::orientation o)
      : vessel("Missile Cruiser", p, 6, 1, "<*\%\%*>", "^*\%\%*V", o){};
  void display_yz();
  void display_xy();
  void attack(){};
  ~missile_cruiser(){};
};
} // namespace battle_ship
#endif