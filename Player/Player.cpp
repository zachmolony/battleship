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

void Player::takeTurn() {
  string input = getInput("Where do you want to fire Captain? (x,y): ", "[a-zA-Z]+,[0-9]+");
  vector<string> coords = split(input, ',');
  
  if (this->theOcean.checkHit(coords)) {
    cout << "Direct Hit, good shot caprain";
  }
}