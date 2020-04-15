#ifndef VESSEL_H
#define VESSEL_H

#include "board.h"
#include "piece.h"
#include <iostream>
#include <string>

namespace battle_ship {
class vessel : public piece {

public:
  vessel() = default;
  vessel(std::string n, coordinates p, std::size_t l, std::size_t w,
         std::string xy_rep_hor, std::string xy_rep_ver, orientation o,
         std::string u, std::size_t ap)
      : piece(n, p, l, w, xy_rep_hor, xy_rep_ver, u, o, ap){};
  void display_yz();
  virtual void display_xy() = 0;
  ~vessel() = default;
};
} // namespace battle_ship
#endif