#ifndef PIECE_H
#define PIECE_H

#include "rules.h"
#include <iostream>
namespace battle_ship {
class piece {
private:
  battle_ship::x_axis start_x;
  battle_ship::y_axis start_y;
  // Defined as distance on the x-axis
  size_t length;
  // Defined as distance on the y-axis
  size_t width;

public:
  // No default constructor since piece must be defined somewhere
  piece(battle_ship::x_axis x, battle_ship::y_axis y, size_t l, size_t w);
  ~piece() = default;
};
} // namespace battle_ship
#endif