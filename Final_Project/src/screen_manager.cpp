#include "screen_manager.h"
#include <iostream>
#include <string>

// read each input stream line by line, printing them side by side
void battle_ship::screen_manager::side_by_side(
    std::istream &player_stream, std::istream &enemy_stream,
    std::istream &notification_stream, std::size_t width) {

  using namespace std::string_literals;
  std::string line1;
  std::string pad{std::string("                        ")};
  std::cout << "Your Board:" << pad << "Enemy Board" << pad << "Events"
            << std::endl;
  while (std::getline(player_stream, line1)) {
    pad = std::string(width, ' ');
    std::string line2;
    std::string line3;
    // get same line from second stream
    std::getline(enemy_stream, line2);
    std::getline(notification_stream, line3);

    // print them size by the side the correct distance (pad)
    std::cout << line1 << pad << line2 << pad << line3 << std::endl;
  }
}