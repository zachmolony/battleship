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
  system( "read -n 1 -s -p \"Press any key to continue...\n\"" );
  if (system("CLS")) system("clear");
  showTitle();
}

Game::Game() {
  Game::readConfigData();
  showTitle();
  string name = getInput("What is your name? ");
  if (system("CLS")) system("clear");
  switch (Game::menu()) {
    case 0:
      exit(1);
    case 1:
      this->players.push_back(Player(false, name));
      this->players[0].theOcean = Ocean(this->oceanWidth, this->oceanHeight, name);
      this->players.push_back(Player(true, "CPU"));
      this->players[1].theOcean = Ocean(this->oceanWidth, this->oceanHeight, "CPU");
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
  }
  Game::startGame();
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

int Game::menu() {
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
    int x = randomInt(oceanWidth); // todo test
    int y = randomInt(oceanHeight);
    cout << "CPU Fires at " << x << y << endl;
    return { x, y };
  } else { // human player
    // get shot coordinates
    cout << "\n\n" << player.name << "'s Turn\n";
    auto [x, y] = getValidCoords("Where do you want to fire? (x,y): ", oceanWidth, oceanHeight);
    return { x, y };
  }
}

void Game::startGame() {
  newScreen();
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
