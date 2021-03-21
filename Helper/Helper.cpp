#include <iostream>//defines the standard devices cin, cout, clog, ceer; for more info see http://www.cplusplus.com/reference/iostream/
#include <string> //defines string types and conventions including begin & end iterator; for more info see http://www.cplusplus.com/reference/string/
#include <regex>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

long maximum = numeric_limits<streamsize>::max();
long minimum = numeric_limits<streamsize>::min();

int randomInt(int max) {
  random_device rd;     // initialised engine
  mt19937 rng(rd());    // Mersenne-Twister engine
  uniform_int_distribution<int> uni(0, max); // guaranteed unbiased
  return uni(rng);
}

bool randomBool() {
  return randomInt(1) == 1;
}

void sleep(int seconds = 3) {
	this_thread::sleep_for(chrono::milliseconds(seconds * 1000)); // we have to convert the seconds to miliseconds 
}

// string capitalise(string s) { // todo
//   return transform(s.begin(), s.end(),s.begin(), ::toupper);
// }

int getIndexFromLetter(string s) {
  transform(s.begin(), s.end(),s.begin(), ::toupper); // to uppercase

  char* char_array; // convert to char array via pointer
  char_array = &s[0];

  if (strlen(char_array) == 1) { // for single letters return position via ascii
    return (char_array[0] - 'A');
  }
  string firstLetter(1, char_array[0]); // for larger coords use recursion
  return (getIndexFromLetter(firstLetter) * 26) + (char_array[1] - 'A' + 1);
}

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
  cout << prompt;
  cin >> answer;

  while(!regex.empty()) {
    std::regex re(regex);

    if(!std::regex_match(answer, re)){
      cin.clear();
      cin.ignore(maximum, '\n');
      cout << "Incorrect input, try again: ";
      cin >> answer;
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
  cout << endl;
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

tuple<int, int> getValidCoords(string prompt, int xMax, int yMax) {
  while (1) {
    string input = getInput(prompt, "[a-zA-Z]+,[0-9]+");
    vector<string> coords = split(input, ',');
    int x = stoi(coords[1]);
    int y = getIndexFromLetter(coords[0]);
    if (x > xMax || y > yMax) {
      cout << "Invalid coordinate, try again. " << endl;
      continue;
    }
    return { x, y };
  }
} 

string getColumnString(int n) {
   string str = "";
   while (n) {
      int rem = n % 26;
      if (rem == 0) {
         str += 'Z';
         n = (n / 26) - 1;
      }
      else {
         str += (rem - 1) + 'A';
         n = n / 26;
      }
   }
   reverse(str.begin(), str.begin() + str.length());
   return str;
}

// tuple<int, int> getRandomCoords() {
//   vector<string> coords = split(input, ',');
//   return { stoi(coords[1]), getIndexFromLetter(coords[0]) };
// }
