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

  vector<vector<Square>> getGrid(int oceanWidth, int oceanHeight);

  Ocean(int oceanWidth, int oceanHeight); // Constructor that takes the ocean dimensions.

  void showOcean();
};

#endif // ADASHIP_OCEAN_H
