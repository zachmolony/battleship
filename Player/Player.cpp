#include <string>
#include <iostream>
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
  if (this->isComputer) {
    this->theOcean.autoPlaceShips(ships);
    return;
  }
  if (getInput("Do you want to manually place ships? (y/n): ", "[YNyn]") == "y") {
    this->theOcean.autoPlaceShips(ships);
    return;
  }
}

void Player::takeTurn() {
  string input = getInput("Where do you want to fire Captain? (x,y): ", "[0-9]+,[a-zA-Z]+");
  input
}