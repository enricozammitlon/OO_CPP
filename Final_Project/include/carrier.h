#ifndef CARRIER_H
#define CARRIER_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
class carrier : public vessel {

public:
  carrier() = default;
  carrier(coordinates p, orientation o)
      : vessel("Carrier", p, 5, 1, "<-+->", "^|+|V", o,
               "Final_Project/img/carrier.txt", 1){};
  ~carrier() = default;
};
} // namespace battle_ship
#endif