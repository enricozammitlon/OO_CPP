#include "highscore_manager.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::tuple<std::string, size_t>>
    battle_ship::highscore_manager::all_highscores;

void battle_ship::highscore_manager::initialise_highscores() {
  std::ifstream highscores_file;
  highscores_file.open("../saves/Highscores");
  while (!highscores_file.eof()) {
    std::string uname;
    size_t score;
    highscores_file >> uname >> score;
    battle_ship::highscore_manager::add_highscore(
        std::make_tuple(uname, score));
  }
  highscores_file.close();
}

void battle_ship::highscore_manager::add_highscore(
    std::tuple<std::string, size_t> h) {
  // Lambda function to sort by second element of tuple
  auto custom_sort = [](std::tuple<std::string, size_t> lhs,
                        std::tuple<std::string, size_t> rhs) -> bool {
    return std::get<1>(lhs) < std::get<1>(rhs);
  };
  battle_ship::highscore_manager::all_highscores.push_back(h);
  std::sort(battle_ship::highscore_manager::all_highscores.begin(),
            battle_ship::highscore_manager::all_highscores.end(), custom_sort);
  std::ofstream highscores_file;
  highscores_file.open("../saves/Highscores");
  if (battle_ship::highscore_manager::all_highscores.size() > 10) {
    battle_ship::highscore_manager::all_highscores.resize(10);
  }
  for (auto iterator = battle_ship::highscore_manager::all_highscores.begin();
       (iterator != battle_ship::highscore_manager::all_highscores.end());
       iterator++) {
    highscores_file << std::get<0>(*iterator) << " " << std::get<1>(*iterator)
                    << std::endl;
  }
  highscores_file.close();
}