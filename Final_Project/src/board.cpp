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
    for (size_t j{1}; j <= columns; j += 1) {
      board_data[index(i, j)] = "~";
    }
  }
};

battle_ship::board::board(const board &b) {
  board_data = nullptr;
  rows = b.rows;
  columns = b.columns;
  last_filled_row = b.last_filled_row;
  // Now copy size and declare new array
  if (rows * columns > 0) {
    board_data = new std::string[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1) {
      for (size_t j{1}; j <= columns; j += 1) {
        board_data[index(i, j)] = b.board_data[index(i, j)];
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
  last_filled_row = b.last_filled_row;
  // Now copy size and declare new array
  if (rows * columns > 0) {
    board_data = new std::string[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1) {
      for (size_t j{1}; j <= columns; j += 1) {
        board_data[index(i, j)] = b.board_data[index(i, j)];
      }
    }
  }
  return *this;
}

battle_ship::board::board(board &&arr) {
  rows = arr.rows;
  columns = arr.columns;
  last_filled_row = arr.last_filled_row;
  board_data = arr.board_data;
  arr.rows = 0;
  arr.columns = 0;
  arr.last_filled_row = 0;
  arr.board_data = nullptr;
}

battle_ship::board &battle_ship::board::operator=(board &&arr) {
  std::swap(rows, arr.rows);
  std::swap(columns, arr.columns);
  std::swap(last_filled_row, arr.last_filled_row);
  std::swap(board_data, arr.board_data);
  return *this;
}
// Must be changed to accept a point instead of row column
std::size_t battle_ship::board::index(std::size_t m, std::size_t n) const {
  if (m > 0 && m <= rows && n > 0 && n <= columns)
    return (n - 1) + (m - 1) * columns;
  else {
    throw "Error: out of range";
  }
}
std::string &battle_ship::board::operator()(battle_ship::x_axis m,
                                            std::size_t n) const {
  return board_data[index(size_t(m), n)];
};

void battle_ship::board::operator<<(battle_ship::piece *p) {
  if (size_t(p->get_start().x_begin) - 1 + p->get_length() > columns ||
      p->get_start().y_begin - 1 + p->get_width() > rows) {
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
  for (size_t i{}; i < p->get_width(); i += 1) {
    for (size_t j{}; j < p->get_length(); j += 1) {
      board_data[index(p->get_start().y_begin + i,
                       size_t(p->get_start().x_begin) + j)] =
          p->get_xy_representation()[i + j * p->get_width()];
    }
  }
  all_pieces.push_back(p);
}

bool battle_ship::board::take_hit(battle_ship::point target_point) {
  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    battle_ship::piece *current_piece = *iterator;

    if (battle_ship::rules::do_intersect(current_piece->get_start(),
                                         current_piece->get_end(), target_point,
                                         target_point)) {
      board_data[index(target_point.y_begin, size_t(target_point.x_begin))] =
          "H";
      current_piece->hit(target_point);
      return true;
    }
  }
  board_data[index(target_point.y_begin, size_t(target_point.x_begin))] = "M";
  return false;
}

namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const board &b) {
  if (b.rows == 0 && b.columns == 0) {
    os << "Board is empty!" << std::endl;
    return os;
  }
  os << "     ";
  for (size_t j{0}; j < b.columns; j += 1) {
    os << char(65 + j) << " ";
  }
  os << std::endl;
  os << "___|_";
  for (size_t j{0}; j < b.columns; j += 1) {
    os << "__";
  }
  os << "|" << std::endl;
  for (size_t i{1}; i <= b.rows; i += 1) {
    for (size_t j{1}; j <= b.columns; j += 1) {
      std::string padding{"  "};
      if (i >= 10) {
        padding = " ";
      }
      if (j == 1) {
        os << i << padding << "| ";
      }
      std::string current_character{b.board_data[b.index(i, j)]};
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
