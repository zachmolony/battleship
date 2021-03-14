#ifndef ADASHIP_PLAYER_H
#define ADASHIP_PLAYER_H

#include <string>
#include "../Ship/Ship.h"
#include "../Ocean/Ocean.h"

using namespace std;


class Player {
  public:
    string name;
    bool isComputer;
    vector<Ship> ships;
    Ocean theOcean;

    Player(bool isComputer, string name);
    void initGame();
    void placeShips(vector<vector<string>> ships);
    void showOcean();
    void takeTurn();
};

#endif // ADASHIP_PLAYER_H
