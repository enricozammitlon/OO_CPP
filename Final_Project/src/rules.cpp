#include "rules.h"
#include <algorithm>
#include <string>

std::string battle_ship::rules::current_turn{"Your"};

bool battle_ship::rules::on_segment(coordinates p, coordinates q,
                                    coordinates r) {
  if (std::size_t(q.col) <= std::max(std::size_t(p.col), std::size_t(r.col)) &&
      std::size_t(q.col) >= std::min(std::size_t(p.col), std::size_t(r.col)) &&
      q.row <= std::max(p.row, r.row) && q.row >= std::min(p.row, r.row))
    return true;

  return false;
};

int battle_ship::rules::orientation(coordinates p, coordinates q,
                                    coordinates r) {
  // See https://www.geeksforgeeks.org/orientation-3-ordered-coordinatess/
  // for details of below formula.
  int val = (q.row - p.row) * (std::size_t(r.col) - std::size_t(q.col)) -
            (std::size_t(q.col) - std::size_t(p.col)) * (r.row - q.row);

  if (val == 0)
    return 0; // colinear

  return (val > 0) ? 1 : 2; // clock or counterclock wise
};
// See
// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool battle_ship::rules::do_intersect(coordinates start_1, coordinates end_1,
                                      coordinates start_2, coordinates end_2) {
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
  if (o1 == 0 && on_segment(start_1, start_2, end_1))
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
