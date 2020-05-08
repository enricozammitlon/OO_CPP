#include "authentication.h"
#include "player.h"
#include <experimental/filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

void battle_ship::authentication::signup(
    std::shared_ptr<battle_ship::human> &p) {
  namespace fs = std::experimental::filesystem;

  std::cout << "Welcome, new commander. What shall we call you?" << std::endl;
  std::string uname;
  std::cin >> uname;
  std::string path = "../saves/Users/" + uname + ".profile";
  if (fs::exists(path)) {
    std::cout << "Username already taken." << std::endl;
    return;
  }
  std::string pass_confirm;
  std::string pass;
  std::cout << "Great. What is your chosen password, sir?" << std::endl;
  std::cin >> pass;
  std::cout << "Could you confirm that password,sir?" << std::endl;
  std::cin >> pass_confirm;
  if (pass != pass_confirm) {
    std::cout << "Passwords do not match!" << std::endl;
    return;
  }
  std::ofstream profile_file;
  profile_file.open("../saves/Users/" + uname + ".profile");
  profile_file << std::hash<std::string>{}(pass) << " " << std::string::npos;
  profile_file.close();
  p.reset();
  p = std::make_shared<battle_ship::human>(uname, std::string::npos,
                                           std::hash<std::string>{}(pass));
  return;
}

void battle_ship::authentication::signin(
    std::shared_ptr<battle_ship::human> &p) {
  namespace fs = std::experimental::filesystem;
  std::cout << "Welcome back, commander. What is your username?" << std::endl;
  std::string uname;
  std::cin >> uname;
  std::string path = "../saves/Users/" + uname + ".profile";
  if (!fs::exists(path)) {
    std::cout << "No user with this name exists!" << std::endl;
    return;
  }
  std::string pass;
  std::cout << "Great. What is your password, sir?" << std::endl;
  std::cin >> pass;
  std::ifstream profile_file;
  profile_file.open("../saves/Users/" + uname + ".profile");
  if (!profile_file.good()) {
    std::cout << "IO Error." << std::endl;
    return;
  } else {
    size_t pass_hash;
    size_t highscore;
    profile_file >> pass_hash >> highscore;
    profile_file.close();
    if (pass_hash == std::hash<std::string>{}(pass)) {
      p.reset();
      p = std::make_shared<battle_ship::human>(uname, highscore,
                                               std::hash<std::string>{}(pass));
      return;
    } else {
      std::cout << "Incorrect password!" << std::endl;
      return;
    }
  }
}