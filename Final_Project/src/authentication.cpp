#include "authentication.h"
#include "player.h"
#include <experimental/filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

battle_ship::player *battle_ship::authentication::signup() {
  namespace fs = std::experimental::filesystem;

  std::cout << "Welcome, new commander. What shall we call you?" << std::endl;
  std::string uname;
  std::cin >> uname;
  std::string path = "../saves/" + uname + ".profile";
  if (fs::exists(path)) {
    std::cout << "Username already taken." << std::endl;
    return nullptr;
  }
  std::string pass_confirm;
  std::string pass;
  std::cout << "Great. What is your chosen password, sir?" << std::endl;
  std::cin >> pass;
  std::cout << "Could you confirm that password,sir?" << std::endl;
  std::cin >> pass_confirm;
  if (pass != pass_confirm) {
    std::cout << "Passwords do not match!" << std::endl;
    return nullptr;
  }
  std::ofstream profile_file;
  profile_file.open("../saves/" + uname + ".profile");
  profile_file << std::hash<std::string>{}(pass) << " " << 0;
  profile_file.close();
  return new player(uname, true, std::hash<std::string>{}(pass));
}

battle_ship::player *battle_ship::authentication::signin() {
  namespace fs = std::experimental::filesystem;
  std::cout << "Welcome back, commander. What is your username?" << std::endl;
  std::string uname;
  std::cin >> uname;
  std::string path = "../saves/" + uname + ".profile";
  if (!fs::exists(path)) {
    std::cout << "No user with this name exists!" << std::endl;
    return nullptr;
  }
  std::string pass;
  std::cout << "Great. What is your password, sir?" << std::endl;
  std::cin >> pass;
  std::ifstream profile_file;
  profile_file.open("../saves/" + uname + ".profile");
  if (!profile_file.good()) {
    std::cout << "IO Error." << std::endl;
    return nullptr;
  } else {
    size_t pass_hash;
    size_t highscore;
    profile_file >> pass_hash >> highscore;
    if (pass_hash == std::hash<std::string>{}(pass)) {
      return new player(uname, true, std::hash<std::string>{}(pass));
    } else {
      std::cout << "Incorrect password!" << std::endl;
      return nullptr;
    }
  }
}