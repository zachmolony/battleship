#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "Game.h"
#include "../Player/Player.h"
#include "../Helper/Helper.h"

using namespace std;

void showWinner(string playerName) {
  cout << R"(             ___________)" << endl; 
  cout << R"(            '._==_==_=_.')" << endl;
  cout << R"(            .-\:      /-.)" << endl;
  cout << R"(           | (|:.     |) |)" << endl;
  cout << R"(            '-|:.     |-')" << endl;
  cout << R"(              \::.    /)" << endl;
  cout << R"(               '::. .')" << endl;
  cout << R"(                 ) ()" << endl;
  cout << R"(               _.' '._)" << endl;
  cout << R"(              '"""""""')" << endl;
  cout << "              " << setw(9) << playerName << endl << endl << endl;
  cout << "       " << "Congratulations!!!" << endl << endl;
}

void showTitle() {
  cout << "██████╗░░█████╗░████████╗████████╗██╗░░░░░███████╗░██████╗██╗░░██╗██╗██████╗░" << endl;
  cout << "██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║░░░░░██╔════╝██╔════╝██║░░██║██║██╔══██╗" << endl;
  cout << "██████╦╝███████║░░░██║░░░░░░██║░░░██║░░░░░█████╗░░╚█████╗░███████║██║██████╔╝" << endl;
  cout << "██╔══██╗██╔══██║░░░██║░░░░░░██║░░░██║░░░░░██╔══╝░░░╚═══██╗██╔══██║██║██╔═══╝░" << endl;
  cout << "██████╦╝██║░░██║░░░██║░░░░░░██║░░░███████╗███████╗██████╔╝██║░░██║██║██║░░░░░" << endl;
  cout << "╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░░░░╚═╝░░░╚══════╝╚══════╝╚═════╝░╚═╝░░╚═╝╚═╝╚═╝░░░░░" << endl << endl;
}

void newScreen() {
  system( "read -n 1 -s -p \"Press any key to continue...\"" );
  if (system("CLS")) system("clear");
  showTitle();
}

Game::Game() {
  Game::readConfigData();
  switch (Game::menu()) {
    case 0:
      exit(1);
    case 1:
      setupGame(1, false, false);
      break;
    case 2:
      setupGame(2, false, false);
      break;
    case 3:
      setupGame(1, true, false);
      break;
    case 4:
      setupGame(2, true, false);
      break;
    case 5:
      setupGame(1, false, true);
      break;
    case 6:
      setupGame(2, false, true);
      break;
    case 7:
      setupGame(0, false, true);
      break;
  }
  startGame();
};

Game::~Game() {
  for (Player *p  : players){
    delete p;
  }
}

void Game::readConfigData() {
  const string FILE_NAME = "adaship_config.ini";
  ifstream file(FILE_NAME);

  string line;

  while (getline(file, line)) {
    // setup variables to split each record into
    stringstream stream(line);
    string field;

    while (getline(stream, field)) { // split the line from identifier and data
      vector<string> splitLine = split(field, ':');
      if (splitLine[0] == "Board") {
        string str = removeWhitespace(splitLine[1]);
        vector<string> coords = split(str, 'x'); // get coords
        this->oceanHeight = stoi(coords[0]); // todo struct
        this->oceanWidth = stoi(coords[1]);
      }
      if (splitLine[0] == "Boat") {
        string str = removeWhitespace(splitLine[1]);
        vector<string> ship = split(str, ',');
        this->boats.push_back(ship);
      }
    }
  }
  file.close();
};

void Game::setupGame(int humanPlayers, bool salvo, bool hiddenmines) {
  for (int x = 0; x < humanPlayers; x++) {
    string playerName = "Player " + to_string(x + 1);
    Player *player = new Player(false, playerName);
    player->theOcean = new Ocean(this->oceanWidth, this->oceanHeight, playerName);
    this->players.push_back(player);
  }
  for (int x = 0; x < humanPlayers % 2; x++) {
    string playerName = "CPU " + to_string(x + 1);
    Player *player = new Player(true, playerName);
    player->theOcean = new Ocean(this->oceanWidth, this->oceanHeight, playerName);
    this->players.push_back(player);
  }
  if (salvo) this->salvo = true;
}

int Game::menu() {
  if (system("CLS")) system("clear");
  showTitle();
  cout << setw(3) << '*' << ' ' << setw(4) << ' ';
  cout << "Choose a game mode: " << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "1: Player vs CPU " << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "2: Player vs Player " << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "3: Player vs CPU (Salvo)" << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "4: Player vs Player (Salvo)" << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "5: Player vs CPU (Hidden Mines)" << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "6: Player vs Player (Hidden Mines)" << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "7: CPU vs CPU (Hidden Mines)" << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "0: Quit " << endl << endl;

  // return 1;

  int choice = getIntegerInput("Enter an option: ", 0, 7);
  cout << endl;
  return choice;
}

void Game::takeTurn(Player* player, Player* opponent) {
  if (salvo) {
    if (player->isComputer) {
      for (int i = 0; i < player->remainingShips(); i++) {
        int x = randomInt(oceanWidth) + 1;
        int y = randomInt(oceanHeight) + 1;
        cout << "CPU Fires at " << x << y << endl;
        sleep(1);
        opponent->theOcean->oceanGrid[x][y]->handleTorpedo(opponent->name);
      }
      return;
    } else {
      vector<tuple<int, int>> shots = getSalvoCoords("Where do you want to fire? (x,y e.g. A,2) : ", oceanWidth, oceanHeight, player->remainingShips());
      for (int i = 0; i < shots.size(); i++) {
        auto [x, y] = shots[i];
        opponent->theOcean->oceanGrid[x][y]->handleTorpedo(opponent->name);
      }
    }
  } else {
    // cpu player
    if (player->isComputer) {
      int x = randomInt(oceanWidth) + 1;
      int y = randomInt(oceanHeight) + 1;
      cout << "CPU Fires at " << x << y << endl;
      sleep(1);
      opponent->theOcean->oceanGrid[x][y]->handleTorpedo(opponent->name);
      return;
    } else { // human player
      // get shot coordinates
      cout << "\n\n" << player->name << "'s Turn\n";
      auto [x, y] = getValidCoords("Where do you want to fire? (x,y e.g. A,2) : ", oceanWidth, oceanHeight);
      opponent->theOcean->oceanGrid[x][y]->handleTorpedo(opponent->name);
    }    
  }
}

string Game::playGame() {
  while (true) { // turn mechanics
    for (int p = 0; p < this->players.size(); p++) {
      int opp = p^1; // get other index: flip 1 <-> 0

      // show opponents ocean
      this->players[opp]->showOcean();

      takeTurn(this->players[p], this->players[opp]);

      this->players[opp]->theOcean->showOcean();
      cout << endl << endl;
      newScreen();
      if (players[opp]->remainingShips() == 0) {
        return this->players[p]->name;
      }
    }
  }
}

void Game::startGame() {
  if (system("CLS")) system("clear");
  showTitle();
  cout << "Starting Game... " << endl << endl; // todo clear screen on turn
  for (int x = 0; x < this->players.size(); x++) {
    this->players[x]->theOcean->showOcean();
    this->players[x]->placeShips(this->boats);
    newScreen();
  }

  string winner = playGame();
  showWinner(winner);
}
