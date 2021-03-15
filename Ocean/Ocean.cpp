#include <vector>
#include <iostream>
#include "Ocean.h"
#include "../Square/Square.h"
#include "../Ship/Ship.h"
#include "../Helper/Helper.h"

using namespace std;

bool randomBool() { // not a very balanced random implementation but for this use i dont really care
  return 0 + (rand() % (1 - 0 + 1)) == 1;
}

int randomInt(int max) {
  srand((unsigned)time(0));
  return (rand() % max) + 1; 
}

Ocean::Ocean() {};

Ocean::Ocean(int oceanWidth, int oceanHeight) {
  this->oceanWidth = oceanWidth;
  this->oceanHeight = oceanHeight;
  this->oceanGrid = getGrid(oceanWidth, oceanHeight);
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

  for (unsigned int i = 0; i < oceanWidth + 1; i++) {
    vector<Square> row;
    for (unsigned int j = 0; j < oceanHeight + 1; j++) {
      row.emplace_back(Square());
    }
    grid.push_back(row);
  }

  return grid;
}

void Ocean::showOcean() {
  for (int x = 0; x < oceanWidth + 1; x++) { // for each row, format
    if (x == 0) {
      cout << ' ' << ' ' << "|";
    }
    else if (x > 0 && x < 10) {
      cout << " " << x << "|";
    }
    else {
      cout << x << "|";
    }
    for (int y = 0; y < oceanHeight + 1; y++) {
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

void Ocean::autoPlaceShips(vector<vector<string>> boats) {
  for (int i = 0; i < boats.size(); i++) { // for each boat
    Ship ship = Ship(stoi(boats[i][1]), boats[i][0]);
    cout << "Placing " << ship.name << endl;
    bool placed = false;
    while (!placed) {
      bool horizontal = randomBool();
      int x = randomInt(this->oceanWidth);
      int y = randomInt(this->oceanHeight);
      placed = placeShip(x, y, horizontal, ship.parts, ship.name, ship);
    }
  }
}

bool Ocean::placeShip(int x, int y, bool horizontal, int size, string name, Ship &ship) {
  if (horizontal) {
    if (x + size > oceanWidth + 1) { // check is not too far to the edge
      return false;
    }
    for (int squarecount = 0; squarecount < size; squarecount++) { // for the length of the ship
      if (this->oceanGrid[x][y + squarecount].isShip) { // check no ship exists on that square
        return false;
      }
    }
     // place the ship once we know the spots are free
    for (int remainingSquares = 0; remainingSquares < size; remainingSquares++) {
      this->oceanGrid[x][y + remainingSquares].placeShip(name, ship);
    };
  } else { // same thing for horizontal
    if (x + size > oceanWidth + 1) {
      return false;
    }
    for (int squarecount = 0; squarecount < size; squarecount++) { 
      if (this->oceanGrid[x + squarecount][y].isShip) {
        return false;
      }
    }
    for (int remainingSquares = 0; remainingSquares < size; remainingSquares++) {
      this->oceanGrid[x + remainingSquares][y].placeShip(name, ship);
    };
  }
  return true;
};

bool Ocean::checkHit(vector<string> coords) {
  int x = getIndexFromLetter(coords[0]);
  int y = stoi(coords[1]);
  cout << 65 - x << y << endl;
  return true;
}