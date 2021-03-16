#include <string>
#include <iostream>
#include <vector>
#include "../Player/Player.h"
#include "../Ship/Ship.h"
#include "../Ocean/Ocean.h"
#include "../Helper/Helper.h"

using namespace std;


Player::Player(bool isComputer, string name) {
  this->name = name;
  this->isComputer = isComputer;
};

void Player::showOcean() {
  this->theOcean.showOcean();
};

void Player::placeShips(vector<vector<string>> ships) {
  this->theOcean.autoPlaceShips(ships);
  Player::showOcean();
  return;
  if (this->isComputer) {
    this->theOcean.autoPlaceShips(ships);
    return;
  }
  if (getInput("Do you want to manually place ships? (y/n): ", "[YNyn]") == "y") {
    this->theOcean.autoPlaceShips(ships);
    return;
  }
}

// void Player::checkHit(coords) {
//   if (this->theOcean.checkHit(coords)) {
//     cout << "Direct hit! Good shot Captain. " << endl;
//   } else {
//     cout << "That was a miss Captain, adjust your fire. " << endl;
//   }
// }