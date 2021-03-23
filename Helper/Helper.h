#ifndef INPUT_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define INPUT_H

#include <string>
#include <limits>

using namespace std;

vector<tuple<int, int>> getSalvoCoords(string prompt, int xMax, int yMax, int shipsLeft);

tuple<int, int> getValidCoords(string prompt, int xMax, int yMax);

int randomInt(int max);

bool randomBool();

void sleep(int seconds = 3);

int getIndexFromLetter(string s);

vector<string> split(string toSplit, char delimiter);

string removeWhitespace(string str);

string getInput(string prompt, const string regex = "");

int getIntegerInput(string prompt, long min = numeric_limits<streamsize>::min(), long max = numeric_limits<streamsize>::max());

float getFloatInput(string prompt, long min = numeric_limits<streamsize>::min(), long max = numeric_limits<streamsize>::max());

string getColumnString(int n);

#endif
