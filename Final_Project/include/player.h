#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <string>
#include <vector>
namespace battle_ship {
class player {
protected:
  std::string username;
  std::unique_ptr<board> player_board;
  std::weak_ptr<player> enemy;
  int budget{500};
  std::vector<coordinates> already_targeted;
  bool ready_to_play;
  std::string subdir;

public:
  player() = default;
  player(std::string uname, bool ready, std::string sub)
      : username{uname}, ready_to_play{ready}, subdir{sub} {
    reset();
  };
  std::string get_uname() { return username; };
  void assign_enemy(std::shared_ptr<player> e) { enemy = e; };
  player &get_enemy() { return *(enemy.lock()); };
  void modify_budget(int money) { budget += money; };
  void reset();
  bool is_ready_to_play() { return ready_to_play; };
  int get_budget() { return budget; }
  virtual void winning_line() = 0;
  virtual void attack(piece &attacking_piece, player &enemy) = 0;
  virtual size_t get_highscore() = 0;
  virtual void save_highscore(size_t h) = 0;
  board &get_board() { return *player_board; };
  ~player() = default;
};
} // namespace battle_ship
#endif