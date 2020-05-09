#ifndef HIGH_H
#define HIGH_H

#include <string>
#include <tuple>
#include <vector>
namespace battle_ship {
/*!
 * \class highscore_manager
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Used to hold all highscores and mange the highscore state
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Wed, 15 Apr 2020 13:29:30
 */
class highscore_manager {
public:
  static std::vector<std::tuple<std::string, size_t>> all_highscores;
  static void add_highscore(std::tuple<std::string, size_t> h);
  static void initialise_highscores();
};
} // namespace battle_ship
#endif