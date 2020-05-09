#ifndef NPC_H
#define NPC_H
#include "player.h"
#include <string>

namespace battle_ship {
/*!
 * \class npc
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief A type of player, implements methods targeted for non-playable
 * characters (computer controlled)
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Wed, 15 Apr 2020 17:55:28
 */
class npc : public virtual player {
private:
  /// Placeholder for future implementations
  size_t difficulty{1};

public:
  npc() = default;
  npc(std::string uname, size_t diff)
      : player(uname, true, "AI"), difficulty{diff} {};
  /// Returns a line to be outputted when the user effectively loses
  void winning_line();
  /// The NPC should not be saved in the all time highscores
  size_t get_highscore() { return std::string::npos; };
  /// The NPC should not be saved in the all time highscores
  void save_highscore(size_t h){};
  void attack(piece &attacking_piece, player &enemy);
  ~npc() = default;
};
} // namespace battle_ship
#endif