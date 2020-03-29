#ifndef SLOOP_H
#define SLOOP_H

#include "rules.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
class sloop : public vessel {

public:
  sloop() = default;
  sloop(battle_ship::point p, battle_ship::orientation o)
      : vessel("Sloop", p, 3, 1, "<+>", "^+V", o, "Final_Project/img/sloop.txt",
               2){};
  void display_xy(){};
  ~sloop(){};
};
} // namespace battle_ship
#endif