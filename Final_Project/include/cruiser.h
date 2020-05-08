#ifndef CRUISER_H
#define CRUISER_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
class cruiser : public vessel {

public:
  cruiser() = default;
  cruiser(coordinates p, orientation o)
      : vessel("Cruiser", p, 4, 1, "<++>", "^++V", o,
               "Final_Project/img/cruiser.txt", 1){};
  ~cruiser() = default;
};
} // namespace battle_ship
#endif