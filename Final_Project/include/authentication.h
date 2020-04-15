#ifndef AUTH_H
#define AUTH_H
#include "human.h"

namespace battle_ship {
class authentication {
public:
  static void signup(std::shared_ptr<human> &p);
  static void signin(std::shared_ptr<human> &p);
};
} // namespace battle_ship
#endif