#ifndef ADASHIP_SQUARE_H
#define ADASHIP_SQUARE_H

#include <vector>
#include <string>

using namespace std;


class Square {

private:

public:
  bool isShip;
  bool isHit;
  string identifier = "^";
  string shipType;

  string handleTorpedo();

  Square(bool isShip, string identifier, string shipType); // constructor

  string getIdentifier();
};

#endif // ADASHIP_SQUARE_H
