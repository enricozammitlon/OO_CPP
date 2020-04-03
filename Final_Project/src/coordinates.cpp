#include "coordinates.h"
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const coordinates &p) {
  os << "(";
  os << char(std::size_t(p.col) + 64);
  os << ",";
  os << p.row;
  os << ")" << std::endl;
  return os;
};
std::istream &operator>>(std::istream &is, coordinates &p) {
  std::string input;
  std::getline(is, input);
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
      return is;
    } else {
      // err
    }
  } else {
    // err
  }
  return is;
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