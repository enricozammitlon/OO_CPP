#include "piece.h"

battle_ship::piece::piece(battle_ship::x_axis x, battle_ship::y_axis y,
                          size_t l, size_t w) {
  start_x = x;
  start_y = y;
  length = l;
  width = w;
};