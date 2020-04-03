#ifndef VESSEL_H
#define VESSEL_H
#include "board.h"
#include "player.h"
#include "rules.h"
#include <string>
namespace battle_ship {
class player {
protected:
  std::string username;
  std::size_t highscore{0};
  battle_ship::board *player_board;
  battle_ship::board *enemy_board;
  std::size_t budget{battle_ship::rules::initial_budget};

public:
  player() = default;
  player(std::string uname, battle_ship::board *pb, battle_ship::board *eb)
      : username{uname}, player_board{pb}, enemy_board{eb} {};
  virtual ~player(){};
};
} // namespace battle_ship
#endif