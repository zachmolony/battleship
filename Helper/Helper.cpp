#include <iostream>//defines the standard devices cin, cout, clog, ceer; for more info see http://www.cplusplus.com/reference/iostream/
#include <string> //defines string types and conventions including begin & end iterator; for more info see http://www.cplusplus.com/reference/string/
#include <regex>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

long maximum = std::numeric_limits<std::streamsize>::max();
long minimum = std::numeric_limits<std::streamsize>::min();

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

string getInput(string prompt, const string regex = "") {
  string answer;
  do {
    cout << prompt;
    getline(cin, answer);
  } while (answer.empty());

  while(!regex.empty()){
    std::regex re(regex);
    getline(cin, answer);
    if(!std::regex_match(answer, re)){
      cout << "Invalid value, please try again: ";
      continue;
    }
    return answer;
  }
  return answer;
}

int getIntegerInput(string prompt, long min, long max) {
  int number;
  cout << prompt;
  cin >> number;
  while(1) {
    if(cin.fail() || number > max || number < min) {
      cin.clear();
      cin.ignore(maximum, '\n');
      cout << "Incorrect input, try again: ";
      cin >> number;
    } else {
      break;
    }
  }
  return number;
}

float getFloatInput(string prompt, long min = minimum, long max = maximum) {
  float number;
  cout << prompt;
  cin >> number;
  while(1) {
    if(cin.fail() || number > max || number < min) {
      cin.clear();
      cin.ignore(maximum, '\n');
      cout << "Incorrect input, try again: ";
      cin >> number;
    } else {
      break;
    }
  }
  return number;
}
