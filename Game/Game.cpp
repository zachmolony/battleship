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


Game::Game() {
  Game::readConfigData();
  int thing = Game::menu();
  switch (thing) {
    case 0:
      exit(1);
    case 1:
      this->players.push_back(Player(false, "Zach"));
      this->players[0].theOcean = Ocean(this->oceanWidth, this->oceanHeight);
      this->players.push_back(Player(true, "CPU"));
      this->players[1].theOcean = Ocean(this->oceanWidth, this->oceanHeight);
      Game::startGame();
      // PlayerinitGame();
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

int Game::menu() {
  cout << setfill('*') << setw(40) << endl;
  cout << setw(3) << '*' << ' ' << setw(4) << ' ';
  cout << "Choose a game mode: " << endl;
  // cout << ' ' << setw(13) << ' ' << setw(26) << '*' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "1: Player vs CPU " << endl;
  // cout << setfill(' ') << setw(31) << ' ' << setfill('*') << setw(4) << ' ' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "2: Player vs Player " << endl;
  // cout << setfill(' ') << setw(30) << ' ' << setfill('*') << setw(4) << ' ' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "3: Player vs CPU (Salvo)" << endl;
  // cout << setfill(' ') << setw(40) << ' ' << setfill('*') << setw(4) << ' ' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "4: Player vs Player (Salvo)" << endl;
  // cout << setfill(' ') << setw(37) << ' ' << setfill('*') << setw(4) << ' ' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "5: Player vs CPU (Hidden Mines)" << endl;
  // cout << setfill(' ') << setw(34) << ' ' << setfill('*') << setw(4) << ' ' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "6: Player vs Player (Hidden Mines)" << endl;
  // cout << setfill(' ') << setw(30) << ' ' << setfill('*') << setw(4) << ' ' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "7: CPU vs CPU (Hidden Mines)" << endl;
  // cout << setfill(' ') << setw(31) << ' ' << setfill('*') << setw(4) << ' ' << endl;

  cout << setw(3) << '*' << ' ' << setfill(' ') << setw(4) << ' ';
  cout << "0: Quit " << endl;
  // cout << setfill(' ') << setw(31) << ' ' << setfill('*') << setw(4) << ' ' << endl;
  return 1;
}

void Game::startGame() {
  for (int x = 0; x < this->players.size(); x++) {
    this->players[x].placeShips(this->boats);
  }
  while (true) {
    for (int x = 0; x < this->players.size(); x++) {
      this->players[x].takeTurn();
    }
  }
}
