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
battle_ship::market::get_available_pieces(battle_ship::player *p) {
  std::vector<std::string> available_pieces = all_pieces;
  for (auto iterator = p->get_board().get_pieces().begin();
       iterator != p->get_board().get_pieces().end(); iterator++) {
    battle_ship::piece *current_piece = *iterator;
    for (auto secondary_iterator = available_pieces.begin();
         secondary_iterator != available_pieces.end(); secondary_iterator++) {
      if (current_piece->get_name() == *secondary_iterator) {
        available_pieces.erase(secondary_iterator);
      }
    }
    // Here check the price of the current piece before making it available
  }
  return available_pieces;
}

std::tuple<bool, std::string>
battle_ship::market::buy_piece(battle_ship::player *p, std::string piece_name,
                               battle_ship::coordinates coors,
                               battle_ship::orientation orientation) {
  if (piece_name == "Sloop") {
    battle_ship::piece *piece_to_add =
        new battle_ship::sloop(coors, orientation);
    p->get_board() << piece_to_add;
    p->modify_budget(-100);
    return std::make_tuple(true, "Transaction successful.");
  } else {
    return std::make_tuple(false, "Unknown piece name.");
  }
}

std::tuple<bool, std::string>
battle_ship::market::sell_piece(battle_ship::player *p,
                                std::string piece_name) {
  std::vector<battle_ship::piece *> current_pieces =
      p->get_board().get_pieces();
  battle_ship::piece *element_to_delete;
  bool found = false;
  size_t position{0};
  for (auto iterator = current_pieces.begin(); iterator != current_pieces.end();
       iterator++) {
    if (piece_name == (*iterator)->get_name()) {
      element_to_delete = *iterator;
      found = true;
      break;
    }
    position += 1;
  }
  if (found) {
    p->get_board().remove_piece(element_to_delete, position);
    p->modify_budget(100);
    return std::make_tuple(true, "Transaction successful.");
  } else {
    return std::make_tuple(false, "Unknown piece name.");
  }
}