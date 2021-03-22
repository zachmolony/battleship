#ifndef ADASHIP_OCEAN_H
#define ADASHIP_OCEAN_H

#include <vector>
#include "../Square/Square.h"
#include "../Ship/Ship.h"

using namespace std;


class Ocean {
  private:
    string playerName;

  public:
    int oceanHeight;
    int oceanWidth;
    vector<vector<Square*>> oceanGrid;

    Ocean(); // dummy constructor
    Ocean(int oceanWidth, int oceanHeight, string playerName); // Constructor that takes the ocean dimensions.
    ~Ocean();
    vector<vector<Square*>> &getGrid();


    bool placeShip(int x, int y, bool direction, int size, string name, Ship* ship);

    void showOcean();
};

#endif // ADASHIP_OCEAN_H
