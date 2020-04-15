#include "npc.h"
#include <iostream>

void battle_ship::npc::winning_line() {
  std::cout << "Commander...*cough*...we've been defated by " << username << "."
            << std::endl;
}