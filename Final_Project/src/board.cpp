#include "board.h"
#include "geometry.h"
#include <array>
#include <iterator>
#include <vector>

battle_ship::board::board() {
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
  if (rows * columns > 0) {
    board_data = std::make_unique<std::string[]>(rows * columns);
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
    return *this;
  board_data = nullptr;
  rows = b.get_rows();
  columns = b.get_cols();
  if (rows * columns > 0) {
    board_data = std::make_unique<std::string[]>(rows * columns);
    for (size_t i{1}; i <= rows; i += 1) {
      for (size_t j{size_t(battle_ship::x_axis::A)}; j <= columns; j += 1) {
        battle_ship::coordinates current_coordinates{
            static_cast<battle_ship::x_axis>(j), i};
        modify_coordinate(current_coordinates, b(current_coordinates));
      }
    }
  }
  return *this;
}

battle_ship::board::board(board &&b) {
  rows = b.get_rows();
  columns = b.get_cols();
  board_data = std::move(b.board_data);
  all_pieces = std::move(b.all_pieces);
  b.rows = 0;
  b.columns = 0;
  b.board_data = nullptr;
  b.all_pieces.clear();
}

battle_ship::board &battle_ship::board::operator=(board &&b) {
  std::swap(rows, b.rows);
  std::swap(columns, b.columns);
  std::swap(board_data, b.board_data);
  std::swap(all_pieces, b.all_pieces);
  return *this;
}
/// Returns the index needed to access a coordinate in a flat array structure
size_t battle_ship::board::index(const battle_ship::coordinates &p) const {
  if (p.row > 0 && p.row <= rows && size_t(p.col) > 0 &&
      size_t(p.col) <= columns) {
    return (size_t(p.col) - 1) + (p.row - 1) * columns;
  } else {
    std::cerr << "Error: out of range" << std::endl;
    return std::string::npos;
  }
}

std::string
battle_ship::board::operator()(const battle_ship::coordinates &p) const {
  return board_data[index(p)];
};

void battle_ship::board::operator<<(std::unique_ptr<battle_ship::piece> p) {
  if (size_t(p->get_start().col) - 1 + p->get_length() > columns ||
      p->get_start().row - 1 + p->get_width() > rows) {
    std::cerr << "This piece does not fit on the board!" << std::endl;
    return;
  }

  for (auto iterator = all_pieces.begin(); iterator != all_pieces.end();
       iterator++) {
    if (battle_ship::geometry::do_intersect((*iterator)->get_start(),
                                            (*iterator)->get_end(),
                                            p->get_start(), p->get_end())) {
      std::cerr << "This piece intersects with pieces already on the board!"
                << std::endl;
      return;
    }
  }
  /*
  This nested loop adds the actual character representation to the board
  in the coordinates of the point so the user can see it on their terminal later
  */
  size_t rep_i{};
  for (size_t i{p->get_start().row}; i <= p->get_end().row; i += 1) {
    size_t rep_j{};
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
  all_pieces.push_back(std::move(p));
}

void battle_ship::board::remove_piece(size_t pos) {
  size_t rep_i{};
  /*
  This nested loop removes the actual character representation to the board
  in the coordinates of the point to revert it to the empty coordinate
  representation
  */
  for (size_t i{all_pieces[pos]->get_start().row};
       i <= all_pieces[pos]->get_end().row; i += 1) {
    size_t rep_j{};
    for (size_t j{size_t(all_pieces[pos]->get_start().col)};
         j <= size_t(all_pieces[pos]->get_end().col); j += 1) {
      battle_ship::coordinates current_coordinates{
          static_cast<battle_ship::x_axis>(j), i};
      modify_coordinate(current_coordinates, "~");
      rep_j += 1;
    }
    rep_i += 1;
  }
  all_pieces[pos].reset();
  all_pieces.erase(all_pieces.begin() + pos);
}

void battle_ship::board::modify_coordinate(
    battle_ship::coordinates &target_coordinates, std::string new_value) {
  board_data[index(target_coordinates)] = new_value;
}
/*
  This method works by first removing the representation the piece
  was showing on the board and then adding it in the new pose.
  This is different than removing and adding a piece since it would be
  inefficient and would actually delete the piece only to recreate it
  */
void battle_ship::board::edit_piece(battle_ship::piece &p, size_t pos,
                                    battle_ship::coordinates new_coor,
                                    battle_ship::orientation new_orientation) {
  size_t rep_i{};
  for (size_t i{p.get_start().row}; i <= p.get_end().row; i += 1) {
    size_t rep_j{};
    for (size_t j{size_t(p.get_start().col)}; j <= size_t(p.get_end().col);
         j += 1) {
      battle_ship::coordinates current_coordinates{
          static_cast<battle_ship::x_axis>(j), i};
      modify_coordinate(current_coordinates, "~");
      rep_j += 1;
    }
    rep_i += 1;
  }
  p.modify_pose(new_coor, new_orientation);
  rep_i = 0;
  for (size_t i{p.get_start().row}; i <= p.get_end().row; i += 1) {
    size_t rep_j{};
    for (size_t j{size_t(p.get_start().col)}; j <= size_t(p.get_end().col);
         j += 1) {
      battle_ship::coordinates current_coordinates{
          static_cast<battle_ship::x_axis>(j), i};
      board_data[index(current_coordinates)] =
          p.get_xy_representation()[rep_j + rep_i * p.get_length()];
      rep_j += 1;
    }
    rep_i += 1;
  }
}
/// Does not show the enemy the piece positions that have not been hit
battle_ship::board battle_ship::board::mask() const {
  std::unique_ptr<battle_ship::board> masked_board =
      std::make_unique<battle_ship::board>(*this);
  for (size_t i{1}; i <= rows; i += 1) {
    for (size_t j{size_t(battle_ship::x_axis::A)}; j <= columns; j += 1) {
      battle_ship::coordinates current_coordinates{
          static_cast<battle_ship::x_axis>(j), i};
      if ((*this)(current_coordinates) == "H" ||
          (*this)(current_coordinates) == "M" ||
          (*this)(current_coordinates) == "~") {
        masked_board->modify_coordinate(current_coordinates,
                                        (*this)(current_coordinates));
      } else {
        masked_board->modify_coordinate(current_coordinates, "~");
      }
    }
  }
  return *masked_board;
}

namespace battle_ship {
/**Mostly self explanatory, the method used ANSI escape characters to display
 * different colours to show a coordinate which is hit, miss, empty or poulated
 */
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
