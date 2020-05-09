#ifndef CRUISER_H
#define CRUISER_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
/*!
 * \class cruiser
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief A type of vessel
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Wed, 15 Apr 2020 21:32:31
 */
class cruiser : public vessel {
public:
  cruiser() = default;
  cruiser(coordinates p, orientation o)
      : vessel("Cruiser", p, 4, 1, "<++>", "^++V", o, 1){};
  ~cruiser() = default;
};
} // namespace battle_ship
#endif