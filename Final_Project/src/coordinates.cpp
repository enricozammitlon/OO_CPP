#include "coordinates.h"
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const coordinates &p) {
  os << "(";
  os << char(std::size_t(p.col) + 64);
  os << p.row;
  os << ")";
  return os;
};
bool operator>>(std::istream &is, coordinates &p) {
  std::string input;
  is >> input;
  std::smatch match;
  const std::regex find_x{"[A-Z]"};
  const std::regex find_y{"[A-Z][0-9]*"};
  std::string real_part;

  if (std::regex_search(input, match, find_x)) {
    battle_ship::x_axis x{
        static_cast<battle_ship::x_axis>(match[0].str().at(0) - 64)};
    if (std::regex_search(input, match, find_y)) {
      std::string digits_part{
          match[0].str().substr(1, match[0].str().length())};
      std::stringstream temp_stream;
      temp_stream << digits_part;
      std::size_t y;
      temp_stream >> y;
      p.col = x;
      p.row = y;
      if (p.row <= 0 || p.row > 10 || std::size_t(p.col) <= 0 ||
          std::size_t(p.col) > 10) {
        std::cerr << "Coordinates out of range." << std::endl;
        return true;
      }
      return false;
    } else {
      std::cerr << "Not a valid y coordinate." << std::endl;
    }
  } else {
    std::cerr << "Not a valid x coordinate." << std::endl;
  }
  return true;
}
} // namespace battle_ship

battle_ship::coordinates
battle_ship::coordinates::boosted_x(std::size_t length) const {
  return battle_ship::coordinates{
      static_cast<battle_ship::x_axis>(std::size_t(col) + length), row};
};
battle_ship::coordinates
battle_ship::coordinates::boosted_y(std::size_t width) const {
  return battle_ship::coordinates{col, row + width};
};