#ifndef SCRN_MNGR_H
#define SCRN_MNGR_H
#include "game.h"
#include <iostream>

namespace battle_ship {
class screen_manager {
public:
  static void side_by_side(battle_ship::game *game, std::size_t width = 5);
};
} // namespace battle_ship
#endif