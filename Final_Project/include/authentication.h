#ifndef AUTH_H
#define AUTH_H
#include "player.h"

namespace battle_ship {
class authentication {
public:
  static void signup(std::shared_ptr<battle_ship::player> &p);
  static void signin(std::shared_ptr<battle_ship::player> &p);
};
} // namespace battle_ship
#endif