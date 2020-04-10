#ifndef SCRN_MNGR_H
#define SCRN_MNGR_H
#include "board.h"
#include <iostream>

namespace battle_ship {
class screen_manager {
public:
  static void side_by_side(battle_ship::board &player_board,
                           battle_ship::board &computer_board,
                           std::size_t width);
};
} // namespace battle_ship
#endif