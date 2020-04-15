#include "highscore_manager.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::tuple<std::string, int>>
    battle_ship::highscore_manager::all_highscores;

void battle_ship::highscore_manager::initialise_highscores() {
  std::string uname;
  int score;
  std::ifstream highscores_file;
  highscores_file.open("../saves/Highscores");
  while (!highscores_file.eof()) {
    highscores_file >> uname >> score;
    battle_ship::highscore_manager::add_highscore(
        std::make_tuple(uname, score));
  }
  highscores_file.close();
}

void battle_ship::highscore_manager::add_highscore(
    std::tuple<std::string, int> h) {
  // Lambda function to sort by second element of tuple
  auto custom_sort = [](std::tuple<std::string, int> lhs,
                        std::tuple<std::string, int> rhs) -> bool {
    return std::get<1>(lhs) < std::get<1>(rhs);
  };
  battle_ship::highscore_manager::all_highscores.push_back(h);
  std::sort(battle_ship::highscore_manager::all_highscores.begin(),
            battle_ship::highscore_manager::all_highscores.end(), custom_sort);
  std::ofstream highscores_file;
  highscores_file.open("../saves/Highscores");
  for (auto iterator = battle_ship::highscore_manager::all_highscores.begin();
       iterator != battle_ship::highscore_manager::all_highscores.end();
       iterator++) {
    highscores_file << std::get<0>(*iterator) << " " << std::get<1>(*iterator)
                    << std::endl;
  }
  highscores_file.close();
}