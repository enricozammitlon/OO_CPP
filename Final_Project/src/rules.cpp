#include "rules.h"
#include <algorithm>
#include <iterator>
#include <regex>
#include <string>
namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const point &p) {
  os << "(";
  os << char(std::size_t(p.x_begin) + 64);
  os << ",";
  os << p.y_begin;
  os << ")" << std::endl;
};
std::istream &operator>>(std::istream &is, point &p) {
  std::string input;
  std::getline(is, input);
  std::smatch match;
  const std::regex find_x{"[A-Z][0-9]"};
  std::string real_part;

  if (std::regex_search(input, match, find_x)) {
    battle_ship::x_axis x{
        static_cast<battle_ship::x_axis>(match[0].str().at(0) - 64)};
    if (match[0].str() != "") {
      std::stringstream temp_stream;
      temp_stream << match[0].str().at(1);
      std::size_t y;
      temp_stream >> y;
      p.x_begin = x;
      p.y_begin = y;
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

bool battle_ship::rules::on_segment(point p, point q, point r) {
  if (std::size_t(q.x_begin) <=
          std::max(std::size_t(p.x_begin), std::size_t(r.x_begin)) &&
      std::size_t(q.x_begin) >=
          std::min(std::size_t(p.x_begin), std::size_t(r.x_begin)) &&
      q.y_begin <= std::max(p.y_begin, r.y_begin) &&
      q.y_begin >= std::min(p.y_begin, r.y_begin))
    return true;

  return false;
};

int battle_ship::rules::orientation(point p, point q, point r) {
  // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
  // for details of below formula.
  int val = (q.y_begin - p.y_begin) *
                (std::size_t(r.x_begin) - std::size_t(q.x_begin)) -
            (std::size_t(q.x_begin) - std::size_t(p.x_begin)) *
                (r.y_begin - q.y_begin);

  if (val == 0)
    return 0; // colinear

  return (val > 0) ? 1 : 2; // clock or counterclock wise
};
// See
// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool battle_ship::rules::do_intersect(point start_1, point end_1, point start_2,
                                      point end_2) {
  // Find the four orientations needed for general and
  // special cases
  int o1 = orientation(start_1, end_1, start_2);
  int o2 = orientation(start_1, end_1, end_2);
  int o3 = orientation(start_2, end_2, start_1);
  int o4 = orientation(start_2, end_2, end_1);

  // General case
  if (o1 != o2 && o3 != o4)
    return true;

  // Special Cases
  // p1, q1 and p2 are colinear and p2 lies on segment p1q1
  if (o1 == 0 && on_segment(start_1, end_1, start_2))
    return true;

  // p1, q1 and q2 are colinear and q2 lies on segment p1q1
  if (o2 == 0 && on_segment(start_1, end_2, end_1))
    return true;

  // p2, q2 and p1 are colinear and p1 lies on segment p2q2
  if (o3 == 0 && on_segment(start_2, start_1, end_2))
    return true;

  // p2, q2 and q1 are colinear and q1 lies on segment p2q2
  if (o4 == 0 && on_segment(start_2, end_1, end_2))
    return true;

  return false; // Doesn't fall in any of the above cases
}
