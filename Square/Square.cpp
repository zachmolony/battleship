#include <vector>
#include <string>
#include "Square.h"
#include "../Ship/Ship.h"

using namespace std;

Square::Square() {};

Square::Square(bool isShip, string identifier, string shipType) {
  this->isShip = isShip;
  this->identifier = identifier;
  this->shipType = shipType;
}

void Square::placeShip(string name, Ship& ship) {
  this->isShip = true;
  this->identifier = name.at(0);
  this->shipType = name;
  this->shipRef = ship;
}

string Square::getIdentifier() {
  return this->identifier;
}

bool Square::handleTorpedo() {
  if (this->isHit || !this->isShip) {
      return false;
  }
  this->shipRef.handleHit();
  return true;
}
