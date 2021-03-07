#include <string>
#include <iostream>
#include "Ship.h"

using namespace std;

Ship::Ship() {};

Ship::Ship(int length, string shipType) {
  this->parts = length;
  this->name = shipType;
};

void Ship::handleHit() {
  this->parts -= 1;
  if (this->parts == 0) {
    this->isDestroyed = true;
  }
  cout << this->name << " has been hit Captain! Only " << this->parts << " parts remaining!" << endl;
}
