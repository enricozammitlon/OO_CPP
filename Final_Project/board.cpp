// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 26/03/2020
// Final Project
// This class is to create a board and hold pieces for each user

#include "piece.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
class board {
  friend std::ostream &operator<<(std::ostream &os, const board &mat);
  friend std::istream &operator>>(std::istream &is, board &mat);

private:
  double *board_data{nullptr};
  size_t rows{0};
  size_t columns{0};
  size_t last_filled_row{0};

public:
  board() = default;
  board(size_t r, size_t c) {
    rows = r;
    columns = c;
    board_data = new double[rows * columns];
  };
  board(const board &arr);
  board &operator=(const board &arr);
  board(board &&arr);
  board &operator=(board &&arr);
  ~board() { delete[] board_data; };
  size_t get_rows() const { return rows; }
  size_t get_cols() const { return columns; }
  size_t index(size_t m, size_t n) const {
    if (m > 0 && m <= rows && n > 0 && n <= columns)
      return (n - 1) + (m - 1) * columns;
    else {
      throw "Error: out of range";
    }
  }
  size_t get_size() const { return rows * columns; }
  double &operator()(const size_t m, const size_t n) const {
    return board_data[index(m, n)];
  }
};

board::board(const board &arr) {
  board_data = nullptr;
  rows = arr.get_rows();
  columns = arr.get_cols();
  last_filled_row = arr.last_filled_row;
  // Now copy size and declare new array
  if (rows * columns > 0) {
    board_data = new double[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1) {
      for (size_t j{1}; j <= columns; j += 1) {
        board_data[index(i, j)] = arr(i, j);
      }
    }
  }
}

board &board::operator=(const board &arr) {
  if (&arr == this)
    return *this; // no self assignment
  // First delete this object's array
  delete[] board_data;
  board_data = nullptr;
  rows = arr.get_rows();
  columns = arr.get_cols();
  last_filled_row = arr.last_filled_row;
  // Now copy size and declare new array
  if (rows * columns > 0) {
    board_data = new double[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1) {
      for (size_t j{1}; j <= columns; j += 1) {
        board_data[index(i, j)] = arr(i, j);
      }
    }
  }
  return *this;
}

board::board(board &&arr) {
  rows = arr.rows;
  columns = arr.columns;
  last_filled_row = arr.last_filled_row;
  board_data = arr.board_data;
  arr.rows = 0;
  arr.columns = 0;
  arr.last_filled_row = 0;
  arr.board_data = nullptr;
}

board &board::operator=(board &&arr) {
  std::swap(rows, arr.rows);
  std::swap(columns, arr.columns);
  std::swap(last_filled_row, arr.last_filled_row);
  std::swap(board_data, arr.board_data);
  return *this;
}

std::ostream &operator<<(std::ostream &os, const board &mat) {
  if (mat.rows == 0 && mat.columns == 0) {
    os << "board is empty!" << std::endl;
    return os;
  }
  for (size_t i{1}; i <= mat.rows; i += 1) {
    for (size_t j{1}; j <= mat.columns; j += 1) {
      if (j == 1) {
        if (i == 1) {
          os << "( ";
        } else {
          os << "| ";
        }
      }
      os << mat(i, j) << " ";
      if (j == mat.columns) {
        if (i == mat.rows) {
          os << ")";
        } else {
          os << "|";
        }
      }
    }
    os << std::endl;
  }
  return os;
}

std::istream &operator>>(std::istream &is, board &output_board) {
  std::string input;
  std::getline(is, input);
  bool isRow{true};
  const std::regex find_elements{"[+-]?[0-9]+[.]?[0-9]*"};
  board board_to_append;
  auto words_begin =
      std::sregex_iterator(input.begin(), input.end(), find_elements);
  auto words_end = std::sregex_iterator();

  size_t matches_found = std::distance(words_begin, words_end);

  if (matches_found > 0) {
    if (isRow) {
      board mat(1, matches_found);
      int j{1};
      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        mat.board_data[mat.index(1, j)] = stod(match.str());
        j += 1;
      }
      board_to_append = std::move(mat);
    } else {
      board mat{matches_found, 1};
      int j{1};
      for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        mat.board_data[mat.index(j, 1)] = stod(match.str());
        j += 1;
      }
      board_to_append = std::move(mat);
    }
  }
  if (board_to_append.rows != 1) {
    throw "Please add one row at a time.";
  }
  if (board_to_append.columns != output_board.columns) {
    throw "Please make sure you are following the dimensions of the board.";
  }
  for (int j{1}; j <= board_to_append.columns; j += 1) {
    output_board
        .board_data[output_board.index(output_board.last_filled_row + 1, j)] =
        board_to_append(1, j);
  }
  output_board.last_filled_row += 1;
  return is;
}

int main() {
  std::cout << "Demonstration of default constructor." << std::endl;
  board a1;
  std::cout << "board a1:\n" << a1 << std::endl;
  std::cout << "Demonstration of parametrized constructor." << std::endl;
  const size_t m{3};
  const size_t n{3};
  board a2{m, n};
  std::cout << "Input for board 2 of size:"
            << "(" << m << "," << n << ")" << std::endl;
  for (size_t i{1}; i <= a2.get_rows(); i += 1) {
    board input_row;
    std::cout << "Please input row " << i << " of " << a2.get_rows()
              << " as a sequence of elements delimited by any non-numeric "
                 "character/s or spaces."
              << std::endl;
    std::cin >> a2;
  }
  std::cout << "board a2:\n" << a2 << std::endl;
  std::cout << "Deep copy a3 from a2 using copy assignment." << std::endl;
  board a3 = a2;
  std::cout << "board a3:\n" << a3 << std::endl;
  std::cout << "Contents of original board a2 modified for proof that copied "
               "board is unchanged."
            << std::endl;
  a2 = a2 + a3;
  std::cout << "board a2:\n" << a2;
  std::cout << "board a3:\n" << a3 << std::endl;
  std::cout << "Deep copy a4 from a2 using copy constructor." << std::endl;
  board a4{a2};
  std::cout << "board a4:\n" << a4 << std::endl;
  std::cout << "Row and Col 2,2 of original board a2 deleted for proof that "
               "copied board is unchanged."
            << std::endl;
  a2 = a2.get_reduced_board(2, 2);
  std::cout << "board a2:\n" << a2;
  std::cout << "board a4:\n" << a4 << std::endl;
  std::cout << "Move a2 into a4 using move copy constructor." << std::endl;
  board a5{std::move(a2)};
  std::cout << "board a2:\n" << a2;
  std::cout << "board a5:\n" << a5 << std::endl;
  std::cout << "Move a5 into a6 using move assignment." << std::endl;
  board a6 = std::move(a5);
  std::cout << "board a5:\n" << a5;
  std::cout << "board a6:\n" << a6 << std::endl;
  std::cout << "\n--Arithmetic Operations--\n" << std::endl;
  const size_t m_a{3};
  const size_t n_a{3};
  board a{m_a, n_a};
  std::cout << "Input for board a of size:"
            << "(" << m_a << "," << n_a << ")" << std::endl;
  for (size_t i{1}; i <= a.get_rows(); i += 1) {
    board input_row;
    std::cout << "Please input row " << i << " of " << a.get_rows()
              << " as a sequence of elements delimited by any non-numeric "
                 "character/s or spaces."
              << std::endl;
    std::cin >> a;
  }
  const size_t m_b{3};
  const size_t n_b{3};
  board b{m_b, n_b};
  std::cout << "Input for board b of size:"
            << "(" << m_b << "," << n_b << ")" << std::endl;
  for (size_t i{1}; i <= b.get_rows(); i += 1) {
    board input_row;
    std::cout << "Please input row " << i << " of " << b.get_rows()
              << " as a sequence of elements delimited by any non-numeric "
                 "character/s or spaces."
              << std::endl;
    std::cin >> b;
  }
  std::cout << "board a:\n" << a;
  std::cout << "board b:\n" << b;
  std::cout << "(board a + board b)\n" << a + b;
  std::cout << "(board a - board b)\n" << a - b;
  std::cout << "(board a * board b)\n" << a * b;
  std::cout << "Determinant of board a: " << a.determinant(a) << std::endl;
  return 0;
}