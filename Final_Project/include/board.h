#ifndef BOARD_H
#define BOARD_H

#include "coordinates.h"
#include "piece.h"
#include <array>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <vector>
namespace battle_ship {

class board {
  friend std::ostream &operator<<(std::ostream &os, const board &b);

private:
  std::size_t rows{10};
  std::size_t columns{10};
  std::unique_ptr<std::string[]> board_data =
      std::make_unique<std::string[]>(rows * columns);
  std::vector<std::unique_ptr<battle_ship::piece>> all_pieces;

public:
  board();
  board(const board &b);
  board &operator=(const board &b);
  board(board &&b);
  board &operator=(board &&b);
  ~board() = default;
  std::size_t get_rows() const { return rows; }
  std::size_t get_cols() const { return columns; }
  std::vector<std::unique_ptr<battle_ship::piece>> const &get_pieces() {
    return all_pieces;
  }
  std::size_t index(const battle_ship::coordinates &p) const;
  std::size_t get_size() const { return rows * columns; };
  void modify_coordinate(battle_ship::coordinates &target_coordinates,
                         std::string new_value);
  void remove_piece(size_t pos);
  void edit_piece(battle_ship::piece &p, size_t pos,
                  battle_ship::coordinates new_coor,
                  battle_ship::orientation new_orientation);
  void operator<<(std::unique_ptr<battle_ship::piece> p);
  std::string operator()(const battle_ship::coordinates &p) const;
};
} // namespace battle_ship
#endif