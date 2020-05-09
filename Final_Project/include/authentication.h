#ifndef AUTH_H
#define AUTH_H
#include "human.h"

/**
 * \class Authentication
 * \brief This class is meant to
 * be used for the login and signup methods
 * \note Attempts at zen rarely work.
 * \author $Author: Enrico Zammit Lonardelli $
 * \date $Date: Tue, 14 Apr 2020 14:25:47 $
 * Contact: enrico.zammitl@gmail.com
 * Created on: Tue, 14 Apr 2020 14:25:47
 */
namespace battle_ship {
class authentication {
public:
  static void signup(std::shared_ptr<human> &p);
  static void signin(std::shared_ptr<human> &p);
};
} // namespace battle_ship
#endif