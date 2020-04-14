#include "market.h"
#include "piece.h"
#include "sloop.h"
#include <string>
#include <tuple>
#include <vector>

std::vector<std::string> battle_ship::market::all_pieces = {"Sloop"};

// Return the subset of all the available pieces, which includes pieces
// the player does not have already and are affordable given their budget
std::vector<std::string>
battle_ship::market::get_available_pieces(battle_ship::player &p) {
  std::vector<std::string> available_pieces = all_pieces;
  for (auto iterator = p.get_board().get_pieces().begin();
       iterator != p.get_board().get_pieces().end(); iterator++) {
    for (auto secondary_iterator = available_pieces.begin();
         secondary_iterator != available_pieces.end(); secondary_iterator++) {
      if ((*iterator)->get_name() == *secondary_iterator) {
        available_pieces.erase(secondary_iterator);
      }
    }
    // Here check the price of the current piece before making it available
  }
  return available_pieces;
}

std::tuple<bool, std::string>
battle_ship::market::buy_piece(battle_ship::player &p, std::string piece_name,
                               battle_ship::coordinates coors,
                               battle_ship::orientation orientation) {
  if (piece_name == "Sloop") {
    std::unique_ptr<battle_ship::piece> piece_to_add =
        std::make_unique<battle_ship::sloop>(coors, orientation);
    p.get_board() << std::move(piece_to_add);
    p.modify_budget(-100);
    return std::make_tuple(true, "Transaction successful.");
  } else {
    return std::make_tuple(false, "Unknown piece name.");
  }
}

std::tuple<bool, std::string>
battle_ship::market::sell_piece(battle_ship::player &p,
                                std::string piece_name) {
  bool found = false;
  size_t position{0};
  for (auto iterator = p.get_board().get_pieces().begin();
       iterator != p.get_board().get_pieces().end(); iterator++) {
    if (piece_name == (*iterator)->get_name()) {
      found = true;
      break;
    }
    position += 1;
  }
  if (found) {
    p.get_board().remove_piece(position);
    p.modify_budget(100);
    return std::make_tuple(true, "Transaction successful.");
  } else {
    return std::make_tuple(false, "Unknown piece name.");
  }
}