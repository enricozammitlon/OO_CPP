#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "rules.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>
namespace battle_ship {

class board {
  friend std::ostream &operator<<(std::ostream &os, const board &b);

private:
  std::string *board_data{nullptr};
  std::size_t rows{0};
  std::size_t columns{0};
  std::size_t last_filled_row{0};
  std::vector<battle_ship::piece *> all_pieces;

public:
  board() = default;
  board(std::size_t r, std::size_t c);
  board(const board &arr);
  board &operator=(const board &arr);
  board(board &&arr);
  board &operator=(board &&arr);
  ~board() { delete[] board_data; };
  std::size_t get_rows() const { return rows; }
  std::size_t get_cols() const { return columns; }
  std::size_t index(size_t m, std::size_t n) const;
  std::size_t get_size() const { return rows * columns; };
  bool take_hit(battle_ship::point target_point);
  void operator<<(piece *p);
  std::string &operator()(battle_ship::x_axis m, std::size_t n) const;
};
} // namespace battle_ship
#endif