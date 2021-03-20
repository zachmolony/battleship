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
  // autoPlaceShips(ships);
  // Player::showOcean();
  // return;
  if (this->isComputer) {
    cout << endl << endl << "Autoplacing Computer's Ships... " << endl;
    autoPlaceShips(ships);
    theOcean.showOcean();
    return;
  }

  string autoplacing = getInput("Do you want to manually place ships? (y/n): ", "[YNyn]");
  if (autoplacing == "n" || autoplacing == "N") {
    autoPlaceShips(ships);
    theOcean.showOcean();
    return;
  }

  // todo manual ship placement
  for (int i = 0; i < ships.size(); i++) { // for each boat
    Ship ship = Ship(stoi(ships[i][1]), ships[i][0]);
    this->ships.push_back(ship);
    cout << "Placing " << ship.name << endl;

    bool placed = false;
    while (!placed) {
      bool horizontal = randomBool();
      int x = getIntegerInput("", 1, this->theOcean.oceanWidth);
      int y = getIntegerInput("", 1, this->theOcean.oceanHeight);
      placed = this->theOcean.placeShip(x, y, horizontal, ship.parts, ship.name, &ship);
    }
  }
  theOcean.showOcean();
}

void Player::autoPlaceShips(vector<vector<string>> ships) {
  cout << endl;
  for (int i = 0; i < ships.size(); i++) { // for each boat
    Ship ship = Ship(stoi(ships[i][1]), ships[i][0]);
    this->ships.push_back(ship);
    cout << "Placing " << ship.name << endl;

    bool placed = false;
    while (!placed) {
      bool horizontal = randomBool();
      int x = randomInt(this->theOcean.oceanWidth);
      int y = randomInt(this->theOcean.oceanHeight);
      placed = this->theOcean.placeShip(x, y, horizontal, ship.parts, ship.name, &ship);
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