#ifndef ADASHIP_SQUARE_H
#define ADASHIP_SQUARE_H

#include <vector>
#include <string>

using namespace std;


class Square {

private:

public:
  bool isShip = false;
  bool isHit = false;
  string identifier = "-";
  string shipType;

  Square();
  Square(bool isShip, string identifier, string shipType); // constructor

  void placeShip(string name);
  string getIdentifier();
  string handleTorpedo();
};

#endif // ADASHIP_SQUARE_H
