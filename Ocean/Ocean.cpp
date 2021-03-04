#include <vector>
#include <iostream>
#include "Ocean.h"
#include "../Square/Square.h"

using namespace std;

Ocean::Ocean(int oceanWidth, int oceanHeight) {
  this->oceanGrid = getGrid(oceanWidth, oceanHeight);
}

void Ocean::showOcean() {
  cout << oceanHeight << oceanWidth;
  for (int x = 0; x < oceanWidth; x++) {
    for (int y = 0; y < oceanHeight; y++) {
        cout << oceanGrid[x][y].getIdentifier(); // print current square
    }
    cout << endl; // next row
  }
}

// Square Ocean::getGrid(int oceanWidth, int oceanHeight) {
//   Square* grid = (Square*)malloc(sizeof(Square) * oceanWidth);

//   for (int i = 0; i < oceanWidth; i++) {
//     Square* row = (Square*)malloc(sizeof(Square) * oceanHeight);

//     for (int j = 0; j < oceanHeight; j++) {
//       // Square *thing = ;
//       row[j] = Square(true, "^", "yeah"); // add a square to this item
//     }
//     grid[i] = *row; // add this row to the grid
//   }

//   return *grid;
// }

vector<vector<Square>> Ocean::getGrid(int oceanWidth, int oceanHeight) {
  vector<vector<Square>> grid;

  grid.resize(oceanWidth);
  for (unsigned int i = 0; i < oceanWidth; i++) {
    for (unsigned int j = 0; j < oceanHeight; j++) {
      grid[i].resize(oceanHeight);
      grid[i][j] = Square(); // add a square to this item
    }
  }

  return grid;
}
