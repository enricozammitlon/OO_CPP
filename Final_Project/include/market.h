#ifndef MARKET_H
#define MARKET_H
#include "piece.h"
#include "player.h"
#include <string>
#include <tuple>
#include <vector>
namespace battle_ship {
class market {
public:
  static std::vector<std::string> all_pieces;
  static std::vector<std::string> get_available_pieces(battle_ship::player *p);
  static std::tuple<bool, std::string>
  buy_piece(battle_ship::player *p, std::string piece_name,
            battle_ship::coordinates coors,
            battle_ship::orientation orientation);
  static std::tuple<bool, std::string> sell_piece(battle_ship::player *p,
                                                  std::string piece_name);
};
} // namespace battle_ship
#endif