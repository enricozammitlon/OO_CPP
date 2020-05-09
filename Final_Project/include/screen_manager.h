#ifndef SCRN_MNGR_H
#define SCRN_MNGR_H
#include "game.h"
#include <iostream>

namespace battle_ship {
/*!
 * \class screen_manager
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Class used to output to terminal in three coloumns
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Fri, 3 Apr 2020 20:52:38
 */
class screen_manager {
public:
  static void side_by_side(game &game, size_t width = 5);
};
} // namespace battle_ship
#endif