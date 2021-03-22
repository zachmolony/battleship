#include <vector>
#include <iostream>
#include <iomanip>
#include "Ocean.h"
#include "../Square/Square.h"
#include "../Ship/Ship.h"
#include "../Helper/Helper.h"

using namespace std;

Ocean::Ocean() {};

Ocean::Ocean(int oceanWidth, int oceanHeight, string playerName) {
  this->oceanWidth = oceanWidth;
  this->oceanHeight = oceanHeight;
  this->playerName = playerName;

   for (unsigned int i = 0; i < oceanWidth + 1; i++) {
    vector<Square*> row;
    for (unsigned int j = 0; j < oceanHeight + 1; j++) {
      row.emplace_back(new Square());
    }
    oceanGrid.push_back(row);
  }
}

Ocean::~Ocean() {
  for (const auto &row: oceanGrid)
  {
    for (Square *sq: row){
      delete sq;
    }
  }
}

vector<vector<Square*>>& Ocean::getGrid() {
  return oceanGrid;
}

void Ocean::showOcean() {
  // cout << setw(oceanWidth) << '*' << endl;
  cout << "\n\n   " << this->playerName << "'s Board" << endl;
  // cout << setw(oceanWidth) << '*' << endl;
  for (int x = 0; x < oceanWidth + 1; x++) { // for each row, format
    if (x == 0) { // numbering on right side
      cout << ' ' << ' ' << "|";
    }
    else if (x > 0 && x < 10) {
      cout << " " << x << "|";
    }
    else {
      cout << x << "|";
    }
    for (int y = 0; y < oceanHeight + 1; y++) {
      if (x == 0) { // lettering 
        cout << " " << getColumnString(y + 1);
        if (y < 26) {
          cout << ' ';
        }
        cout << "|";
      }
      else { // squares
        cout << ' ' << oceanGrid[x][y]->getIdentifier() << ' ' << "|";
      }
    }
    cout << endl; // next row
  }
  cout << endl;
}


bool Ocean::placeShip(int x, int y, bool horizontal, int size, string name, Ship* ship) {
  if (horizontal) {
    if (x + size > oceanWidth + 1) { // check is not too far to the edge
      return false;
    }
    for (int squarecount = 0; squarecount < size; squarecount++) { // for the length of the ship
      if (this->oceanGrid[x][y + squarecount]->isShip) { // check no ship exists on that square
        return false;
      }
    }
     // place the ship once we know the spots are free
    for (int remainingSquares = 0; remainingSquares < size; remainingSquares++) {
      this->oceanGrid[x][y + remainingSquares]->placeShip(name, ship);
    };
  } else { // same thing for horizontal
    if (x + size > oceanWidth + 1) {
      return false;
    }
    for (int squarecount = 0; squarecount < size; squarecount++) { 
      if (this->oceanGrid[x + squarecount][y]->isShip) {
        return false;
      }
    }
    for (int remainingSquares = 0; remainingSquares < size; remainingSquares++) {
      this->oceanGrid[x + remainingSquares][y]->placeShip(name, ship);
    };
  }
  return true;
};
