#ifndef HIGH_H
#define HIGH_H

#include <string>
#include <tuple>
#include <vector>
namespace battle_ship {
class highscore_manager {
public:
  static std::vector<std::tuple<std::string, int>> all_highscores;
  static void add_highscore(std::tuple<std::string, int> h);
  static void initialise_highscores();
};
} // namespace battle_ship
#endif