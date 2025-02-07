#include "coordinates.h"
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>

namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const coordinates &p) {
  os << "(";
  os << char(size_t(p.col) + 64);
  os << p.row;
  os << ")";
  return os;
};
/**
 * This method works by searching using RegEx for a specific letter
 * and one to two digits. Validation on this for ranges is done and
 * if all checks pass a coordinate is created.
 */
bool operator>>(std::istream &is, coordinates &p) {
  std::string input;
  is >> input;
  std::smatch match;
  const std::regex find_coor{"[A-J]\\d{1,2}"};
  std::string real_part;

  if (std::regex_search(input, match, find_coor)) {
    std::string x_coor{match[0].str()[0]};
    // Capital 'A' in ASCII is value 65
    battle_ship::x_axis x{static_cast<battle_ship::x_axis>(x_coor.at(0) - 64)};
    std::string y_coor{match[0].str().substr(1)};
    std::stringstream temp_stream;
    temp_stream << y_coor;
    size_t y;
    temp_stream >> y;
    p.col = x;
    p.row = y;
    if (p.row <= 0 || p.row > 10 || size_t(p.col) <= 0 || size_t(p.col) > 10) {
      std::cerr << "Coordinates out of range." << std::endl;
      return true;
    }
    return false;
  } else {
    std::cerr << "Not valid coordinates." << std::endl;
  }
  return true;
}
} // namespace battle_ship

battle_ship::coordinates
battle_ship::coordinates::boosted_x(size_t length) const {
  return battle_ship::coordinates{
      static_cast<battle_ship::x_axis>(size_t(col) + length), row};
};
battle_ship::coordinates
battle_ship::coordinates::boosted_y(size_t width) const {
  return battle_ship::coordinates{col, row + width};
};