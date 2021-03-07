#include <vector>
#include <string>
#include "Square.h"

using namespace std;

Square::Square() {};

Square::Square(bool isShip, string identifier, string shipType) {
  this->isShip = isShip;
  this->identifier = identifier;
  this->shipType = shipType;
}

void Square::placeShip(string name) {
  this->isShip = true;
  this->identifier = name.at(0);
  this->shipType = name;
}

string Square::getIdentifier() {
  return this->identifier;
}

string Square::handleTorpedo() {
  if (this->isHit || !this->isShip) {
      return "MISS";
  }
  return "HIT";
}
