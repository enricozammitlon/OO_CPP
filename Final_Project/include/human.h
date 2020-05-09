#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
namespace battle_ship {
class human : public virtual player {
private:
  size_t password_hash;
  size_t highscore{std::string::npos};

public:
  human() = default;
  human(std::string uname, size_t high, size_t pass = 0)
      : player(uname, false, "Users"), password_hash{pass}, highscore{high} {};
  size_t get_highscore() { return highscore; };
  void save_highscore(size_t h);
  void modify_fleet();
  void save_fleet();
  bool add_piece();
  bool remove_piece();
  bool edit_piece();
  void winning_line();
  void attack(piece &attacking_piece, player &enemy);
  ~human() = default;
};
} // namespace battle_ship
#endif