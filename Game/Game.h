#ifndef ADASHIP_GAME_H
#define ADASHIP_GAME_H

#include <vector>
#include "../Ocean/Ocean.h"
#include "../Player/Player.h"

using namespace std;

class Game {
  public:
    int oceanHeight;
    int oceanWidth;
    int score[2] = {0, 0};
    vector<vector<string>> boats;
    vector<Player *> players;

    Game(); // Constructor that takes the ocean dimensions.
    ~Game();

    int menu();
    void setupGame(int humanPlayers, bool salvo, bool hiddenmines);
    void startGame();
    void readConfigData();
    tuple <int, int>takeTurn(Player* player);
};

#endif // ADASHIP_GAME_H
