#ifndef RULES_H
#define RULES_H
#include <string>
namespace battle_ship {
class rules {
private:
  std::string current_turn{0};
  std::size_t initial_budget{1000};

public:
  rules() = default;
  rules(std::string starting_p, std::size_t init_budget)
      : current_turn{starting_p}, initial_budget{init_budget} {};
};
} // namespace battle_ship
#endif