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
  cout << name << " has been hit Captain! Only " << parts << " parts remaining!" << endl;
  parts--;
  if (parts == 0) {
    isDestroyed = true;
  }
  cout << name << " has been hit Captain! Only " << this->parts << " parts remaining!" << endl;
}
