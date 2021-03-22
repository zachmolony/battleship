#ifndef ADASHIP_SHIP_H
#define ADASHIP_SHIP_H

#include <vector>
#include <string>

using namespace std;


class Ship {
  public:
    int parts;
    string name;
    bool isDestroyed = false;

    Ship();
    Ship(int parts, string shipType); // constructor

    void handleHit(string playerName);
};

#endif // ADASHIP_SHIP_H
