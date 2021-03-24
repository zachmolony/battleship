#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include "../Player/Player.h"
#include "../Ship/Ship.h"
#include "../Ocean/Ocean.h"
#include "../Helper/Helper.h"

using namespace std;


Player::Player(bool isComputer, string name) {
  this->name = name;
  this->isComputer = isComputer;
};

Player::~Player() {
  for (Ship *ship: ships) {
    delete ship;
  }
  delete theOcean;
}

void Player::showOcean() {
  this->theOcean->showOcean();
};

void Player::placeShips(vector<vector<string>> ships) {
  if (this->isComputer) {
    cout << endl << endl << "Autoplacing Computer's Ships... " << endl;
    autoPlaceShips(ships);
    theOcean->showOcean();
    return;
  }

  label:
  vector<bool> boolArr(ships.size(), false); // intialise boolean array

  // manual ship placement
  for (int i = 0; i < ships.size(); i++) { // for each boat
    theOcean->showOcean();
    for (int j = 0; j < ships.size(); j++) {
      cout << setw(10) << ships[j][0] << setw(5) << " - " << setw(10) << (boolArr[j] ? "placed" : "unplaced") << endl;
    }
    string option = getInput("\nAutoplace remaining ships? Press R to reset. (y/n/r): ", "[YNRynr]");
    if (option == "r" || option == "R") {
      cout << "Resetting ocean...\n\n";
      theOcean->resetGrid();
      boolArr = vector<bool> (ships.size(), false);
      i = 0;
      clearScreen();
      goto label;
    }
    if (option == "y" || option == "Y") {
      cout << "\nAutoplacing Ships...\n";
      vector<vector<string>> remaining = vector<vector<string>>(ships.begin() + i, ships.end());
      autoPlaceShips(remaining);
      theOcean->showOcean();
      return;
    }

    Ship* pShip = new Ship(stoi(ships[i][1]), ships[i][0]);
    this->ships.push_back(pShip);
    cout << "Placing " << pShip->name << ". Length is " << pShip->parts << endl;

    bool placed = false;
    while (!placed) {
      auto [x, y] = getValidCoords("Enter top right coordinate to place this ship: ", theOcean->oceanWidth, theOcean->oceanHeight);

      bool horizontal = false;
      string orientation = getInput("Enter horizontal or verical (h/v): ", "[HVhv]");
      if (orientation == "H" || orientation == "h") horizontal = true;

      placed = this->theOcean->placeShip(x, y, horizontal, pShip->parts, pShip->name, pShip);
      if (!placed) cout << "Placement failed. Try another coordinate." << endl;
      boolArr[i] = true;
    }
  }
  theOcean->showOcean();
}

void Player::autoPlaceShips(vector<vector<string>> ships) {
  for (int i = 0; i < ships.size(); i++) { // for each boat
    Ship *pShip = new Ship(stoi(ships[i][1]), ships[i][0]);
    this->ships.push_back(pShip);

    bool placed = false;
    while (!placed) {
      bool horizontal = randomBool();
      int x = randomInt(this->theOcean->oceanWidth - 1) + 1;
      int y = randomInt(this->theOcean->oceanHeight - 1) + 1;
      placed = this->theOcean->placeShip(x, y, horizontal, pShip->parts, pShip->name, pShip);
    }
  }
}

int Player::remainingShips() {
  int counter = 0;
  for (int i = 0; i < ships.size(); i++) {
    if (!ships[i]->isDestroyed) {
      counter++;
    }
  }
  return counter;
}
