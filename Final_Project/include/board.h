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
/*!
 * \class board
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Class used to handle board state
 *
 * This class is the owner of its pieces and
 * is in turn owned by the player class.
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Sun, 29 Mar 2020 21:50:33
 */
class board {
  friend std::ostream &operator<<(std::ostream &os, const board &b);

private:
  size_t rows{10};
  size_t columns{10};
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
  size_t get_rows() const { return rows; }
  size_t get_cols() const { return columns; }
  std::vector<std::unique_ptr<piece>> const &get_pieces() { return all_pieces; }
  size_t index(const coordinates &p) const;
  size_t get_size() const { return rows * columns; };
  void modify_coordinate(coordinates &target_coordinates,
                         std::string new_value);
  /** Method to show the board to the opponent
   * for information such as hits or misses
   * without showing the position of the unhit pieces
   */
  board mask() const;
  void remove_piece(size_t pos);
  void edit_piece(piece &p, size_t pos, coordinates new_coor,
                  orientation new_orientation);
  void operator<<(std::unique_ptr<battle_ship::piece> p);
  /// An intuitive getter method
  std::string operator()(const coordinates &p) const;
};
} // namespace battle_ship
#endif