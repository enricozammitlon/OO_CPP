#ifndef VESSEL_H
#define VESSEL_H

#include "board.h"
#include "piece.h"
#include <iostream>
#include <string>

namespace battle_ship {
class vessel : public piece {
protected:
  std::size_t action_points;

public:
  vessel() = default;
  vessel(std::string n, coordinates p, std::size_t l, std::size_t w,
         std::string xy_rep_hor, std::string xy_rep_ver,
         battle_ship::orientation o, std::string u, std::size_t ap)
      : piece(n, p, l, w, xy_rep_hor, xy_rep_ver, u, o) {
    action_points = ap;
  };
  void display_yz();
  virtual void display_xy() = 0;
  void attack(battle_ship::board *player_board,
              battle_ship::board *enemy_board);
  ~vessel(){};
};
} // namespace battle_ship
#endif