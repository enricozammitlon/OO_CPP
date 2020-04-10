// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 26/03/2020
// Final Project : Battle Ship
// This class is to create a board and hold pieces for each user
#include "board.h"
#include "rules.h"
#include <iterator>
#include <stdlib.h>

battle_ship::board::board(std::size_t r, std::size_t c) {
  rows = r;
  columns = c;
  board_data = new std::string[rows * columns];
  for (size_t i{1}; i <= rows; i += 1) {
    for (size_t j{size_t(battle_ship::x_axis::A)}; j <= columns; j += 1) {
      battle_ship::coordinates current_coordinates{
          static_cast<battle_ship::x_axis>(j), i};
      board_data[index(current_coordinates)] = "~";
    }
  }
};

battle_ship::board::board(const board &b) {
  board_data = nullptr;
  rows = b.get_rows();
  columns = b.get_rows();
  // Now copy size and declare new array
  if (rows * columns > 0) {
    board_data = new std::string[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1) {
      for (size_t j{size_t(battle_ship::x_axis::A)}; j <= columns; j += 1) {
        battle_ship::coordinates current_coordinates{
            static_cast<battle_ship::x_axis>(j), i};
        board_data[index(current_coordinates)] = b(current_coordinates);
      }
    }
  }
}

battle_ship::board &battle_ship::board::operator=(const board &b) {
  if (&b == this)
    return *this; // no self assignment
  // First delete this object's array
  delete[] board_data;
  board_data = nullptr;
  rows = b.get_rows();
  columns = b.get_cols();
  // Now copy size and declare new array
  if (rows * columns > 0) {
    board_data = new std::string[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1) {
      for (size_t j{size_t(battle_ship::x_axis::A)}; j <= columns; j += 1) {
        battle_ship::coordinates current_coordinates{
            static_cast<battle_ship::x_axis>(j), i};
        board_data[index(current_coordinates)] = b(current_coordinates);
      }
    }
  }
  return *this;
}

battle_ship::board::board(board &&b) {
  rows = b.get_rows();
  columns = b.get_cols();
  board_data = b.board_data;
  b.rows = 0;
  b.columns = 0;
  b.board_data = nullptr;
}

battle_ship::board &battle_ship::board::operator=(board &&b) {
  std::swap(rows, b.rows);
  std::swap(columns, b.columns);
  std::swap(board_data, b.board_data);
  return *this;
}

battle_ship::board::~board() {
  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    delete *iterator;
  }
  all_pieces.clear();
  delete[] board_data;
};

std::size_t battle_ship::board::index(const battle_ship::coordinates &p) const {
  if (p.row > 0 && p.row <= rows && std::size_t(p.col) > 0 &&
      std::size_t(p.col) <= columns) {
    return (std::size_t(p.col) - 1) + (p.row - 1) * columns;
  } else {
    throw "Error: out of range";
  }
}

std::string &
battle_ship::board::operator()(const battle_ship::coordinates &p) const {
  return board_data[index(p)];
};

void battle_ship::board::operator<<(battle_ship::piece *p) {
  if (size_t(p->get_start().col) - 1 + p->get_length() > columns ||
      p->get_start().row - 1 + p->get_width() > rows) {
    std::cerr << "This piece does not fit on the board!" << std::endl;
    return;
  }

  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    battle_ship::piece *current_piece = *iterator;
    if (battle_ship::rules::do_intersect(current_piece->get_start(),
                                         current_piece->get_end(),
                                         p->get_start(), p->get_end())) {
      std::cerr << "This piece intersects with pieces already on the board!"
                << std::endl;
      return;
    }
  }
  std::size_t rep_i{};
  for (size_t i{p->get_start().row}; i <= p->get_end().row; i += 1) {
    std::size_t rep_j{};
    for (size_t j{size_t(p->get_start().col)}; j <= size_t(p->get_end().col);
         j += 1) {
      battle_ship::coordinates current_coordinates{
          static_cast<battle_ship::x_axis>(j), i};
      board_data[index(current_coordinates)] =
          p->get_xy_representation()[rep_j + rep_i * p->get_length()];
      rep_j += 1;
    }
    rep_i += 1;
  }
  all_pieces.push_back(p);
}

bool battle_ship::board::receive_attempt_hit(
    battle_ship::coordinates &target_coordinates) {
  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    battle_ship::piece *current_piece = *iterator;

    if (battle_ship::rules::do_intersect(
            current_piece->get_start(), current_piece->get_end(),
            target_coordinates, target_coordinates)) {
      board_data[index(target_coordinates)] = "H";
      current_piece->hit(target_coordinates);
      return true;
    }
  }
  board_data[index(target_coordinates)] = "M";
  return false;
}

namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const board &b) {
  if (b.rows == 0 && b.columns == 0) {
    os << "Board is empty!"
       << "\n";
    return os;
  }
  os << std::string(5, ' ');
  for (size_t j{0}; j < b.columns; j += 1) {
    os << char(65 + j) << " ";
  }
  os << " " << std::endl;
  os << "___|_";
  for (size_t j{0}; j < b.columns; j += 1) {
    os << "__";
  }
  os << "|" << std::endl;
  for (size_t i{1}; i <= b.rows; i += 1) {
    for (size_t j{size_t(battle_ship::x_axis::A)}; j <= b.columns; j += 1) {
      battle_ship::coordinates current_coordinates{
          static_cast<battle_ship::x_axis>(j), i};

      std::string padding{"  "};
      if (i >= 10) {
        padding = " ";
      }
      if (j == 1) {
        os << i << padding << "| ";
      }
      std::string current_character{b(current_coordinates)};
      if (current_character == "~") {
        os << "\033[1;34m";
      } else if (current_character == "H") {
        os << "\033[1;31m";
      } else if (current_character == "M") {
        os << "\033[1;33m";
      } else {
        os << "\033[1;32m";
      }
      os << current_character;
      os << "\033[0m ";
      if (j == b.rows) {
        os << "|";
      }
    }
    os << std::endl;
  }
  os << "___|";
  for (size_t j{0}; j < b.columns; j += 1) {
    os << "__";
  }
  os << "_|" << std::endl;
  return os;
}

} // namespace battle_ship
