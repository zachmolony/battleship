#ifndef ADASHIP_SQUARE_H
#define ADASHIP_SQUARE_H

#include <string>
#include "../Ship/Ship.h"

using namespace std;


class Square {

private:

public:
  bool isShip = false;
  bool isHit = false;
  string identifier = "~";
  string shipType;
  Ship* shipRef;

  Square();
  Square(bool isShip, string identifier, string shipType); // constructor

  void placeShip(string name, Ship* ship);
  string getIdentifier();
  bool handleTorpedo();
};

#endif // ADASHIP_SQUARE_H
