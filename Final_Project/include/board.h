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
  std::vector<std::unique_ptr<piece>> all_pieces;

public:
  board();
  board(const board &b);
  board &operator=(const board &b);
  board(board &&b);
  board &operator=(board &&b);
  ~board() = default;
  std::size_t get_rows() const { return rows; }
  std::size_t get_cols() const { return columns; }
  std::vector<std::unique_ptr<piece>> const &get_pieces() { return all_pieces; }
  std::size_t index(const coordinates &p) const;
  std::size_t get_size() const { return rows * columns; };
  void modify_coordinate(coordinates &target_coordinates,
                         std::string new_value);
  board mask() const;
  void remove_piece(size_t pos);
  void edit_piece(piece &p, size_t pos, coordinates new_coor,
                  orientation new_orientation);
  void operator<<(std::unique_ptr<piece> p);
  std::string operator()(const coordinates &p) const;
};
} // namespace battle_ship
#endif