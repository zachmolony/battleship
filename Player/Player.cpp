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

  // manual ship placement
  for (int i = 0; i < ships.size(); i++) { // for each boat
    string keepPlacing = getInput("Do you want to manually place remaining ships? (y/n): ", "[YNyn]");
    if (keepPlacing == "n" || keepPlacing == "N") {
      vector<vector<string>> remaining = vector<vector<string>>(ships.begin() + i, ships.end());
      autoPlaceShips(remaining);
      theOcean.showOcean();
      return;
    }

    Ship ship = Ship(stoi(ships[i][1]), ships[i][0]);
    this->ships.push_back(ship);
    cout << "Placing " << ship.name << ". Length is " << ship.parts << endl;

    bool placed = false;
    while (!placed) {
      auto [x, y] = getValidCoords("Enter top right coordinate to place this ship: ");

      cout << x << " " << y << endl;

      bool horizontal = false;
      string orientation = getInput("Enter horizontal or verical (h/v): ", "[HVhv]");
      if (orientation == "H" || orientation == "h") {
        horizontal = true;
      };

      placed = this->theOcean.placeShip(x, y, horizontal, ship.parts, ship.name, &ship);
      if (!placed) {
        cout << "Placement failed. Try another coordinate." << endl; 
      }
    }
    theOcean.showOcean();
  }
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