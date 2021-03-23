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
    bool salvo = false;
    vector<vector<string>> boats;
    vector<Player *> players;

    Game(); // Constructor that takes the ocean dimensions.
    ~Game();

    int menu();
    void setupGame(int humanPlayers, bool salvo, bool hiddenmines);
    void startGame();
    void readConfigData();
    void takeTurn(Player* player, Player* opponent);
    void takeSalvoTurn(Player* player, Player* opponent);
    string playGame();
};

#endif // ADASHIP_GAME_H
