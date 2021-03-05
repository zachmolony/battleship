#ifndef ADASHIP_OCEAN_H
#define ADASHIP_OCEAN_H

#include <vector>
#include "../Square/Square.h"

using namespace std;


class Ocean {

private:

public:
  int oceanHeight;
  int oceanWidth;
  vector<vector<Square>> oceanGrid;


  Ocean(); // dummy constructor
  Ocean(int oceanWidth, int oceanHeight); // Constructor that takes the ocean dimensions.


  vector<vector<Square>> getGrid(int oceanWidth, int oceanHeight);
  void showOcean();
  void placeShips(vector<vector<string>> boats);
};

#endif // ADASHIP_OCEAN_H
