#ifndef ADASHIP_SHIP_H
#define ADASHIP_SHIP_H

#include <vector>
#include <string>

using namespace std;


class Ship {

private:

public:
  int parts;
  string name;
  bool isDestroyed = false;

  Ship();
  Ship(int parts, string shipType); // constructor

  void handleHit();
};

#endif // ADASHIP_SHIP_H
