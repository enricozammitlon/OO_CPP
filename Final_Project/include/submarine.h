#ifndef submarine_H
#define submarine_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
/*!
 * \class submarine
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief A type of vessel
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Wed, 15 Apr 2020 21:32:31
 */
class submarine : public vessel {
public:
  submarine() = default;
  submarine(coordinates p, orientation o)
      : vessel("Submarine", p, 3, 1, "<*>", "^*V", o, 1){};
  ~submarine() = default;
};
} // namespace battle_ship
#endif