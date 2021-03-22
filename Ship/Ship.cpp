#include <string>
#include <iostream>
#include "Ship.h"

using namespace std;

Ship::Ship() {};

Ship::Ship(int length, string shipType) {
  this->parts = length;
  this->name = shipType;
};

void Ship::handleHit(string playerName) {
  parts--;
  if (parts == 0) {
    isDestroyed = true;
    cout << playerName << "'s " << name << " has been destroyed! " << endl;
  } else {
    cout << "Hit! " << playerName << "'s " << name << " has been hit! Only " << this->parts << " parts remaining!" << endl;
  }
}
