#ifndef ADASHIP_GAME_H
#define ADASHIP_GAME_H

#include <vector>
#include "../Ocean/Ocean.h"
#include "../Player/Player.h"

using namespace std;

class Game {

private:

public:
  int oceanHeight;
  int oceanWidth;
  int score[2] = {0, 0};
  vector<vector<string>> boats;
  vector<Player> players;

  Game(); // Constructor that takes the ocean dimensions.

  int menu();
  void startGame();
  void readConfigData();
};

#endif // ADASHIP_GAME_H
