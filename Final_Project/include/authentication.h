#ifndef AUTH_H
#define AUTH_H
#include "human.h"
#include <memory>
namespace battle_ship {
/*!
 * \class authentication
 *
 * \author Enrico Zammit Lonardelli
 *
 * \brief Class used for login and signup
 *
 * Contact: enrico.zammitl@gmail.com
 *
 * Created on: Tue, 14 Apr 2020 14:25:47
 */
class authentication {
public:
  static void signup(std::shared_ptr<human> &p);
  static void signin(std::shared_ptr<human> &p);
};
} // namespace battle_ship
#endif