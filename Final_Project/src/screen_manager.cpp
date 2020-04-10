#include "screen_manager.h"
#include "board.h"
#include "notification_manager.h"
#include <iostream>
#include <sstream>
#include <string>

// read each input stream line by line, printing them side by side
void battle_ship::screen_manager::side_by_side(
    battle_ship::board &player_board, battle_ship::board &computer_board,
    std::size_t width) {

  battle_ship::notification_manager current_notifications;
  std::stringstream player_stream;
  player_stream << player_board;
  std::stringstream enemy_stream;
  enemy_stream << computer_board;
  std::stringstream notification_stream;
  notification_stream << current_notifications;

  using namespace std::string_literals;
  std::string line1;
  std::string line2;
  std::string line3;
  std::string pad{std::string(width + 15, ' ')};
  std::cout << "Your Board:" << pad << "Your Board:" << pad
            << "Events:" << std::endl;
  while (std::getline(player_stream, line1)) {
    pad = std::string(width, ' ');
    // get same line from second stream
    std::getline(enemy_stream, line2);
    std::getline(notification_stream, line3);

    // print them size by the side the correct distance (pad)
    std::cout << line1 << pad << line2 << pad << line3 << std::endl;
  }
  std::cout << std::endl;
}