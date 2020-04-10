#ifndef SCRN_MNGR_H
#define SCRN_MNGR_H
#include <iostream>
namespace battle_ship {
class screen_manager {
public:
  static void side_by_side(std::istream &player_stream,
                           std::istream &enemy_stream,
                           std::istream &notification_stream,
                           std::size_t width);
};
} // namespace battle_ship
#endif