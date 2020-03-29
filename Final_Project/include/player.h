#ifndef VESSEL_H
#define VESSEL_H
#include "rules.h"
#include <stdlib.h>
#include <string>

namespace battle_ship {
class player {
protected:
  std::string username;
  std::size_t highscore{0};
  std::size_t budget{battle_ship::rules::initial_budget};

public:
  player() = default;
  player(std::string uname) : username{uname} {};
  virtual ~player(){};
};
} // namespace battle_ship
#endif