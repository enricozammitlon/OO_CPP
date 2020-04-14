#ifndef AUTH_H
#define AUTH_H
#include "player.h"

namespace battle_ship {
class authentication {
public:
  static battle_ship::player *signup();
  static battle_ship::player *signin();
};
} // namespace battle_ship
#endif