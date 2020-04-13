#ifndef BOARD_H
#define BOARD_H

#include "coordinates.h"
#include "piece.h"
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
namespace battle_ship {

class board {
  friend std::ostream &operator<<(std::ostream &os, const board &b);

private:
  std::string *board_data{nullptr};
  std::size_t rows{10};
  std::size_t columns{10};
  std::vector<battle_ship::piece *> all_pieces;

public:
  board();
  board(const board &arr);
  board &operator=(const board &arr);
  board(board &&arr);
  board &operator=(board &&arr);
  ~board();
  std::size_t get_rows() const { return rows; }
  std::size_t get_cols() const { return columns; }
  std::vector<battle_ship::piece *> get_pieces() const { return all_pieces; }
  std::size_t index(const battle_ship::coordinates &p) const;
  std::size_t get_size() const { return rows * columns; };
  void modify_coordinate(battle_ship::coordinates &target_coordinates,
                         std::string new_value);
  void remove_piece(battle_ship::piece *p, size_t pos);
  void edit_piece(battle_ship::piece *p, size_t pos,
                  battle_ship::coordinates new_coor,
                  battle_ship::orientation new_orientation);
  void operator<<(piece *p);
  std::string &operator()(const battle_ship::coordinates &p) const;
};
} // namespace battle_ship
#endif