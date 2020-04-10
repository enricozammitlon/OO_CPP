#ifndef BOARD_H
#define BOARD_H

#include "coordinates.h"
#include "piece.h"
#include <iostream>
#include <sstream>
#include <vector>
namespace battle_ship {

class board {
  friend std::ostream &operator<<(std::ostream &os, const board &b);

private:
  std::string *board_data{nullptr};
  std::size_t rows{0};
  std::size_t columns{0};
  std::vector<battle_ship::piece *> all_pieces;

public:
  board() = default;
  board(std::size_t r, std::size_t c);
  board(const board &arr);
  board &operator=(const board &arr);
  board(board &&arr);
  board &operator=(board &&arr);
  ~board();
  std::size_t get_rows() const { return rows; }
  std::size_t get_cols() const { return columns; }
  std::size_t index(const battle_ship::coordinates &p) const;
  std::size_t get_size() const { return rows * columns; };
  bool receive_attempt_hit(battle_ship::coordinates &target_coordinates);
  void operator<<(piece *p);
  std::string &operator()(const battle_ship::coordinates &p) const;
};
} // namespace battle_ship
#endif