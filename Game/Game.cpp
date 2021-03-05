#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "Game.h"
#include "../Ocean/Ocean.h"

using namespace std;

vector<string> split(string toSplit, char delimiter) {
    stringstream ss(toSplit);
    string item;
    vector<string> separated;
    while (getline(ss, item, delimiter)) {
       separated.push_back(item);
    }
    return separated;
}

string removeWhitespace(string str) {
  string::iterator end_pos = remove(str.begin(), str.end(), ' '); // remove whitespace
  str.erase(end_pos, str.end());
  return str;
}





Game::Game() {
  Game::readConfigData();
  Game::initialiseBoard();
  Game::showOcean();
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
        this->oceanWidth = stoi(coords[0]);
        this->oceanHeight = stoi(coords[1]);
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

void Game::initialiseBoard() {
  this->theOcean = Ocean(this->oceanWidth, this->oceanHeight);
  this->theOcean.placeShips(this->boats);
}

void Game::showOcean() {
  this->theOcean.showOcean();
};
