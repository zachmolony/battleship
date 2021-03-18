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
  autoPlaceShips(ships);
  Player::showOcean();
  return;
  if (this->isComputer) {
    autoPlaceShips(ships);
    return;
  }
  if (getInput("Do you want to manually place ships? (y/n): ", "[YNyn]") == "y") {
    autoPlaceShips(ships);
    return;
  }
}

void Player::autoPlaceShips(vector<vector<string>> boats) {
  for (int i = 0; i < boats.size(); i++) { // for each boat
    Ship ship = Ship(stoi(boats[i][1]), boats[i][0]);
    this->ships.push_back(ship);
    cout << "Placing " << ship.name << endl;
    bool placed = false;

    while (!placed) {
      bool horizontal = randomBool();
      int x = randomInt(this->theOcean.oceanWidth);
      int y = randomInt(this->theOcean.oceanHeight);
    }
  }
}

// void Player::checkHit(coords) {
//   if (this->theOcean.checkHit(coords)) {
//     cout << "Direct hit! Good shot Captain. " << endl;
//   } else {
//     cout << "That was a miss Captain, adjust your fire. " << endl;
//   }
// }