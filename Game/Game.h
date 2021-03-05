#ifndef ADASHIP_GAME_H
#define ADASHIP_GAME_H

#include <vector>
#include "../Ocean/Ocean.h"

using namespace std;


class Game {

private:

public:
  int oceanHeight;
  int oceanWidth;
  int score[2] = {0, 0};
  vector<vector<string>> boats;

  Ocean theOcean;

  Game(); // Constructor that takes the ocean dimensions.

  void readConfigData();
  void initialiseBoard();

  void showOcean();
};

#endif // ADASHIP_GAME_H
