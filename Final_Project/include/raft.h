#ifndef RAFT_H
#define RAFT_H

#include "coordinates.h"
#include "vessel.h"
#include <iostream>
namespace battle_ship {
class raft : public vessel {

public:
  raft() = default;
  raft(coordinates p, orientation o)
      : vessel("Raft", p, 2, 1, "<>", "^V", o, "Final_Project/img/raft.txt",
               1){};
  ~raft() = default;
};
} // namespace battle_ship
#endif