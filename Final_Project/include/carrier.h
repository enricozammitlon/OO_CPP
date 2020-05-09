#ifndef CARRIER_H
#define CARRIER_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
/*!
 * \class carrier
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief A type of vessel
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Wed, 15 Apr 2020 21:32:31
 */
class carrier : public vessel {

public:
  carrier() = default;
  carrier(coordinates p, orientation o)
      : vessel("Carrier", p, 5, 1, "<-+->", "^|+|V", o, 1){};
  ~carrier() = default;
};
} // namespace battle_ship
#endif