#ifndef NOTIF_H
#define NOTIF_H

#include <iostream>
#include <string>
#include <vector>
namespace battle_ship {
/*!
 * \class notification_manager
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Used to manage all notifications state
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Fri, 10 Apr 2020 16:31:44
 */
class notification_manager {
  friend std::ostream &operator<<(std::ostream &os,
                                  const notification_manager &n);

private:
  static std::vector<std::string> all_notifications;

public:
  notification_manager() = default;
  static void add_notification(std::string turn, std::string notification);
  static void reset_notifiations() { all_notifications.clear(); };
  ~notification_manager() = default;
};
} // namespace battle_ship
#endif