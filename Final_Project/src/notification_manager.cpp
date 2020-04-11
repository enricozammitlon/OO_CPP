#include "notification_manager.h"
#include <iostream>
#include <iterator>
#include <string>
std::vector<std::string> battle_ship::notification_manager::all_notifications;

namespace battle_ship {
std::ostream &operator<<(std::ostream &os, const notification_manager &n) {
  for (auto iterator = notification_manager::all_notifications.begin();
       iterator != notification_manager::all_notifications.end(); iterator++) {
    os << "["
       << ""
       << " turn] : " << *iterator << std::endl;
  }
  return os;
};
} // namespace battle_ship

void battle_ship::notification_manager::add_notification(
    std::string notification) {
  notification_manager::all_notifications.push_back(notification);
}