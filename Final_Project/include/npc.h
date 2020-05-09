#ifndef NPC_H
#define NPC_H
#include "player.h"
#include <string>

namespace battle_ship {
class npc : public virtual player {
private:
  size_t difficulty{1};

public:
  npc() = default;
  npc(std::string uname, size_t diff)
      : player(uname, true, "AI"), difficulty{diff} {};
  void winning_line();
  size_t get_highscore() { return std::string::npos; };
  void save_highscore(size_t h){};
  void attack(piece &attacking_piece, player &enemy);
  ~npc() = default;
};
} // namespace battle_ship
#endif