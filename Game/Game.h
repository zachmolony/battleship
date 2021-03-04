#ifndef ADASHIP_GAME_H
#define ADASHIP_GAME_H

#include <vector>

using namespace std;


class Game {

private:

public:
  int score[2] = {0, 0};

  Game(); // Constructor that takes the ocean dimensions.

  int readConfigData();

  void showOcean();
};

#endif // ADASHIP_GAME_H
