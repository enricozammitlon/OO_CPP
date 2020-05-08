#ifndef submarine_H
#define submarine_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
class submarine : public vessel {

public:
  submarine() = default;
  submarine(coordinates p, orientation o)
      : vessel("Submarine", p, 3, 1, "<*>", "^*V", o,
               "Final_Project/img/submarine.txt", 1){};
  ~submarine() = default;
};
} // namespace battle_ship
#endif