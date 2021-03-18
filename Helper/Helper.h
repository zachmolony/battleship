#ifndef INPUT_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define INPUT_H

#include <string>
#include <limits>

using namespace std;

bool randomBool();

int randomInt(int max);

int getIndexFromLetter(string s);

vector<string> split(string toSplit, char delimiter);

string removeWhitespace(string str);

string getInput(string prompt, const string regex = "");

int getIntegerInput(string prompt, long min = numeric_limits<streamsize>::min(), long max = numeric_limits<streamsize>::max());

float getFloatInput(string prompt, long min = numeric_limits<streamsize>::min(), long max = numeric_limits<streamsize>::max());

#endif
