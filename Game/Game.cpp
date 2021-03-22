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
};

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
    Player player = Player(false, playerName);
    player.theOcean = Ocean(this->oceanWidth, this->oceanHeight, playerName);
    this->players.push_back(player);
  }
  for (int x = 0; x < humanPlayers % 2; x++) {
    string playerName = "CPU " + to_string(x + 1);
    Player player = Player(true, playerName);
    player.theOcean = Ocean(this->oceanWidth, this->oceanHeight, playerName);
    this->players.push_back(player);
  }
  

  Game::startGame();
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

tuple <int, int>Game::takeTurn(Player& player) {
  // cpu player
  if (player.isComputer) {
    int x = randomInt(oceanWidth);
    int y = randomInt(oceanHeight);
    cout << "CPU Fires at " << x << y << endl;
    sleep();
    return { x, y };
  } else { // human player
    // get shot coordinates
    cout << "\n\n" << player.name << "'s Turn\n";
    auto [x, y] = getValidCoords("Where do you want to fire? (x,y): ", oceanWidth, oceanHeight);
    return { x, y };
  }
}

void Game::startGame() {
  if (system("CLS")) system("clear");
  showTitle();
  cout << "Starting Game... " << endl << endl; // todo clear screen on turn
  for (int x = 0; x < this->players.size(); x++) {
    this->players[x].theOcean.showOcean();
    this->players[x].placeShips(this->boats);
    newScreen();
  }

  while (players[0].remainingShips() != 0 && players[1].remainingShips() != 0) { // turn mechanics
    for (int p = 0; p < this->players.size(); p++) {
      int opp = p^1; // get other index: flip 1 <-> 0

      // show opponents ocean
      this->players[opp].showOcean();

      auto [x, y] = takeTurn(this->players[p]);

      // handle shot on other player's board
      auto& oppOcean = this->players[opp].theOcean;

      auto [isHit] = oppOcean.oceanGrid[x][y].handleTorpedo();
      oppOcean.showOcean();
      if (players[p].isComputer) {
        if (isHit) {
          cout << "Our ship has been hit Captain! ";
        } else {
          cout << "Miss! Our fleet is safe Captain. ";
        }
      } else {
        if (isHit) {
          cout << "Direct hit! Good shot Captain. ";
        } else {
          cout << "That was a miss Captain, adjust your fire. ";
        }
      }
      cout << endl << endl;
      newScreen();
    }
  }
}
