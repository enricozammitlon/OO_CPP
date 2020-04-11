#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include "piece.h"
#include <string>
namespace battle_ship {
class player {
protected:
  std::string username;
  std::size_t highscore{0};
  battle_ship::board *player_board{new battle_ship::board()};
  battle_ship::player *enemy;
  std::size_t budget;

public:
  player() = default;
  player(std::string uname) : username{uname} {};
  std::string get_uname() { return username; };
  void set_budget(std::size_t b) { budget = b; };
  void buy_piece(battle_ship::piece *p){};
  void assign_enemy(battle_ship::player *e) { enemy = e; };
  battle_ship::board *get_board() { return player_board; };
  ~player() { delete player_board; };
};
} // namespace battle_ship
#endif