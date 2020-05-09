#include "notification_manager.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
std::vector<std::string> battle_ship::notification_manager::all_notifications =
    {""};

namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const notification_manager &n) {
  std::vector<std::string>::iterator iterator_start;
  // 12 is due to the board having 10 rows with upper and lower padding
  if (notification_manager::all_notifications.size() > 12) {
    iterator_start = notification_manager::all_notifications.end() - 12;
  } else {
    iterator_start = notification_manager::all_notifications.begin();
  }
  for (auto iterator = iterator_start;
       iterator != notification_manager::all_notifications.end(); iterator++) {
    os << *iterator << std::endl;
  }
  return os;
};
} // namespace battle_ship

void battle_ship::notification_manager::add_notification(
    std::string turn, std::string notification) {
  notification = "[" + turn + "] " + notification;
  notification_manager::all_notifications.push_back(notification);
}