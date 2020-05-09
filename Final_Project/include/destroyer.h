#ifndef DESTROYER_H
#define DESTROYER_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
/*!
 * \class destroyer
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief A type of vessel
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Wed, 15 Apr 2020 21:32:31
 */
class destroyer : public vessel {
public:
  destroyer() = default;
  destroyer(coordinates p, orientation o)
      : vessel("Destroyer", p, 3, 1, "<+>", "^+V", o, 1){};
  ~destroyer() = default;
};
} // namespace battle_ship
#endif