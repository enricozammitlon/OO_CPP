#ifndef DESTROYER_H
#define DESTROYER_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
class destroyer : public vessel {

public:
  destroyer() = default;
  destroyer(coordinates p, orientation o)
      : vessel("Destroyer", p, 3, 1, "<+>", "^+V", o,
               "Final_Project/img/destroyer.txt", 1){};
  ~destroyer() = default;
};
} // namespace battle_ship
#endif