#include <vector>
#include <string>
#include <iostream>
#include "Square.h"
#include "../Ship/Ship.h"

using namespace std;

Square::Square() {};

Square::Square(bool isShip, string identifier, string shipType) {
  this->isShip = isShip;
  this->identifier = identifier;
  this->shipType = shipType;
}

void Square::placeShip(string name, Ship* ship) {
  this->isShip = true;
  this->identifier = name.at(0);
  this->shipType = name;
  this->shipRef = ship;
}

string Square::getIdentifier() {
  return this->identifier;
}

void Square::handleTorpedo(string playerName) {
  if (this->isHit || !this->isShip) {
    this->identifier = ".";
    cout << "Miss! " << playerName << "'s fleet is safe. ";
    return;
  }
  this->identifier = "*";
  this->shipRef->handleHit(playerName);
  return;
}
