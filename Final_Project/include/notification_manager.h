#ifndef NOTIF_H
#define NOTIF_H

#include <iostream>
#include <string>
#include <vector>
namespace battle_ship {
class notification_manager {
  friend std::ostream &operator<<(std::ostream &os,
                                  const notification_manager &n);

private:
  static std::vector<std::string> all_notifications;

public:
  notification_manager() = default;
  static void add_notification(std::string notification);
  ~notification_manager() = default;
};
} // namespace battle_ship
#endif