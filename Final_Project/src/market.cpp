#include "market.h"
#include "carrier.h"
#include "cruiser.h"
#include "destroyer.h"
#include "piece.h"
#include "raft.h"
#include "submarine.h"
#include <string>
#include <tuple>
#include <vector>

std::vector<std::string> battle_ship::market::all_pieces = {
    "Submarine", "Carrier", "Raft", "Cruiser", "Destroyer"};

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
  std::unique_ptr<battle_ship::piece> piece_to_add;
  if (piece_name == "Raft") {
    piece_to_add = std::make_unique<battle_ship::raft>(coors, orientation);
  } else if (piece_name == "Destroyer") {
    piece_to_add = std::make_unique<battle_ship::destroyer>(coors, orientation);
  } else if (piece_name == "Cruiser") {
    piece_to_add = std::make_unique<battle_ship::cruiser>(coors, orientation);
  } else if (piece_name == "Carrier") {
    piece_to_add = std::make_unique<battle_ship::carrier>(coors, orientation);
  } else if (piece_name == "Submarine") {
    piece_to_add = std::make_unique<battle_ship::submarine>(coors, orientation);
  } else {
    return std::make_tuple(false, "Unknown piece name.");
  }
  if (p.get_budget() - piece_to_add->get_cost() >= 0) {
    p.modify_budget(-piece_to_add->get_cost());
    p.get_board() << std::move(piece_to_add);
    return std::make_tuple(true, "Transaction successful.");
  } else {
    return std::make_tuple(false, "No money left,sir.");
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
    p.modify_budget(p.get_board().get_pieces()[position]->get_cost());
    p.get_board().remove_piece(position);
    return std::make_tuple(true, "Transaction successful.");
  } else {
    return std::make_tuple(false, "Unknown piece name.");
  }
}