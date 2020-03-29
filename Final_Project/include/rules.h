#ifndef RULES_H
#define RULES_H
#include <cstddef>
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
struct point {
  friend std::ostream &operator<<(std::ostream &os, const point &p);
  friend std::istream &operator>>(std::istream &is, point &p);
  x_axis x_begin;
  std::size_t y_begin;
};
class rules {
public:
  static int orientation(point p, point q, point r);
  static bool on_segment(point p, point q, point r);
  static bool do_intersect(point start_1, point end_1, point start_2,
                           point end_2);
  static const std::size_t initial_budget{1000};
};
} // namespace battle_ship
#endif