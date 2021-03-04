#include <vector>
#include <string>
#include "Square.h"

using namespace std;

Square::Square(bool isShip, string identifier, string shipType) {
  this->isShip = isShip;
  this->identifier = identifier;
  this->shipType = shipType;
}

// Square::Square() {}; // dummy constructor

string Square::getIdentifier() {
  return this->identifier;
}

string Square::handleTorpedo() {
  if (this->isHit || !this->isShip) {
      return "MISS";
  }
  return "HIT";
}
