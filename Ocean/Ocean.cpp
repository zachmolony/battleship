#include <vector>
#include <iostream>
#include "Ocean.h"
#include "../Square/Square.h"

using namespace std;

Ocean::Ocean(int oceanWidth, int oceanHeight) {
  this->oceanWidth = oceanWidth;
  this->oceanHeight = oceanHeight;
  this->oceanGrid = getGrid(oceanWidth, oceanHeight);
}

Ocean::Ocean() {};

void Ocean::showOcean() {
  for (int x = 0; x < oceanWidth; x++) { // for each row, format
    if (x == 0) {
      cout << ' ' << ' ' << "|";
    }
    else if (x > 0 && x < 10) {
      cout << " " << x << "|";
    }
    else {
      cout << x << "|";
    }
    for (int y = 0; y < oceanHeight; y++) {
      if (x == 0) {
        cout << " " << char(65 + y) << ' ' << "|"; // todo: add ability for larger board
      }
      else {
        cout << ' ' << oceanGrid[x][y].getIdentifier() << ' ' << "|";
      }
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

  for (unsigned int i = 0; i < oceanWidth; i++) {
    vector<Square> row;
    for (unsigned int j = 0; j < oceanHeight; j++) {
      row.emplace_back(Square(true, "^", "Cruiser"));
    }
    grid.push_back(row);
  }

  return grid;
}
