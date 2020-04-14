#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include <string>
#include <vector>
namespace battle_ship {
class player {
protected:
  std::string username;
  size_t password_hash;
  bool human{false};
  std::size_t highscore{0};
  std::unique_ptr<battle_ship::board> player_board;
  std::weak_ptr<battle_ship::player> enemy;
  int budget{100};
  bool ready_to_play{false};
  std::vector<battle_ship::coordinates> already_targeted;

public:
  player() = default;
  player(std::string uname, bool h, size_t pass = 0)
      : username{uname}, password_hash{pass}, human{h} {
    clean_up();
  };
  std::string get_uname() { return username; };
  bool is_ready_to_play() { return ready_to_play; };
  void assign_enemy(std::shared_ptr<battle_ship::player> e) { enemy = e; };
  battle_ship::player &get_enemy() { return *(enemy.lock()); };
  bool is_human() { return human; };
  void modify_budget(int money) { budget += money; };
  void clean_up();
  void modify_fleet();
  void save_fleet();
  bool add_piece();
  bool remove_piece();
  bool edit_piece();
  void attack(battle_ship::piece &attacking_piece, battle_ship::player &enemy);
  battle_ship::board &get_board() { return *player_board; };
  ~player() = default;
};
} // namespace battle_ship
#endif