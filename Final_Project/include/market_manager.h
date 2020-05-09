#ifndef MARKET_H
#define MARKET_H
#include "piece.h"
#include "player.h"
#include <string>
#include <tuple>
#include <vector>
namespace battle_ship {
/*!
 * \class market_manager
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Used to manage available vessels and transactions via budget checking
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Mon, 13 Apr 2020 09:04:33
 */
class market_manager {
public:
  static std::vector<std::string> all_pieces;
  /**This will return the subset of all the pieces which the player
   * has not yet in their fleet
   */
  static std::vector<std::string> get_available_pieces(player &p);
  static std::tuple<bool, std::string> buy_piece(player &p,
                                                 std::string piece_name,
                                                 coordinates coors,
                                                 orientation orientation);
  static std::tuple<bool, std::string> sell_piece(player &p,
                                                  std::string piece_name);
};
} // namespace battle_ship
#endif