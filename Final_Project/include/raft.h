#ifndef RAFT_H
#define RAFT_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
/*!
 * \class raft
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief A type of vessel
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Wed, 15 Apr 2020 21:32:31
 */
class raft : public vessel {
public:
  raft() = default;
  raft(coordinates p, orientation o)
      : vessel("Raft", p, 2, 1, "<>", "^V", o, 1){};
  ~raft() = default;
};
} // namespace battle_ship
#endif