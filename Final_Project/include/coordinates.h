#ifndef COORS_H
#define COORS_H
#include <iostream>
namespace battle_ship {
enum class x_axis {
  A = 1,
  B = 2,
  C = 3,
  D = 4,
  E = 5,
  F = 6,
  G = 7,
  H = 8,
  I = 9,
  J = 10
};
enum class orientation { horizontal, vertical };
enum class y_axis { start = 1, end = 10 };
struct coordinates {
  friend std::ostream &operator<<(std::ostream &os, const coordinates &p);
  friend bool operator>>(std::istream &is, coordinates &p);
  x_axis col;
  std::size_t row;
  coordinates() = default;
  coordinates(x_axis x, std::size_t y) : col{x}, row{y} {};
  coordinates boosted_x(std::size_t length) const;
  coordinates boosted_y(std::size_t width) const;
};
} // namespace battle_ship
#endif