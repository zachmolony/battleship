#include <vector>
#include <string>
#include <iostream>
#include "Game.h"
#include "../Ocean/Ocean.h"

using namespace std;

Game::Game() {
  Game::readConfigData();
};

int Game::readConfigData() {
    return 1;
};

void Game::showOcean() {
    Ocean ocean = Ocean(5, 5);
    ocean.showOcean();
};
