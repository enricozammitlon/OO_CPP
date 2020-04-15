#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
namespace battle_ship {
class human : public player {
private:
  size_t password_hash;
  std::size_t highscore{std::string::npos};

public:
  human() = default;
  human(std::string uname, size_t high, size_t pass = 0)
      : player(uname, false, "Users"), password_hash{pass}, highscore{high} {};
  bool is_ready_to_play() { return ready_to_play; };
  size_t get_highscore() { return highscore; };
  void save_highscore(size_t h);
  void modify_fleet();
  void save_fleet();
  bool add_piece();
  bool remove_piece();
  bool edit_piece();
  void winning_line();
  void attack(piece &attacking_piece, player &enemy);
  board &get_board() { return *player_board; };
  ~human() = default;
};
} // namespace battle_ship
#endif