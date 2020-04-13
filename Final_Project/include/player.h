#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <string>
namespace battle_ship {
class player {
protected:
  std::string username;
  std::size_t highscore{0};
  battle_ship::board *player_board{new battle_ship::board()};
  battle_ship::player *enemy;
  int budget{100};
  bool ready_to_play{false};

public:
  player() = default;
  player(std::string uname) : username{uname} {};
  std::string get_uname() { return username; };
  bool is_ready_to_play() { return ready_to_play; };
  void assign_enemy(battle_ship::player *e) { enemy = e; };
  void modify_budget(int money) { budget += money; };
  void modify_fleet();
  bool add_piece();
  bool remove_piece();
  bool edit_piece();
  battle_ship::board &get_board() { return *player_board; };
  ~player() { delete player_board; };
};
} // namespace battle_ship
#endif