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

void clearScreen() {
  if (system("CLS")) system("clear");
  showTitle();
}

void newScreen() {
  system( "read -n 1 -s -p \"Press any key to continue...\"" );
  clearScreen();
}

int randomInt(int max) {
  random_device rd;     // initialised engine
  mt19937 rng(rd());    // Mersenne-Twister engine
  uniform_int_distribution<int> uni(0, max); // guaranteed unbiased
  return uni(rng);
}

bool randomBool() {
  return randomInt(1) == 1;
}

void sleep(int seconds = 1) {
	this_thread::sleep_for(chrono::milliseconds(seconds * 1000)); // we have to convert the seconds to miliseconds 
}

int getIndexFromLetter(string s) {
  transform(s.begin(), s.end(),s.begin(), ::toupper); // to uppercase

  char* char_array; // convert to char array via pointer
  char_array = &s[0];

  if (strlen(char_array) == 1) { // for single letters return position via ascii
    return (char_array[0] - 'A');
  }
  string firstLetter(1, char_array[0]); // for larger coords use recursion to find remainder
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

vector<tuple<int, int>> getSalvoCoords(string prompt, int xMax, int yMax, int shipsLeft) {
  vector<tuple<int, int>> shots;
  label:
  while (1) {
    string input = getInput(prompt, "[a-zA-Z]+,[0-9]+");

    vector<string> coordsPairs = split(input, ' '); // todo bug here - pairs not high enough

    if (coordsPairs.size() != shipsLeft) {
      cout << coordsPairs.size() << shipsLeft << endl;
      cout << "Invalid number of coordinates - try entering " << shipsLeft << " pairs of coordinates separated by spaces. " << endl;
      continue;
    }

    for (int i = 0; i < shipsLeft; i++) {
      vector<string> coords = split(input, ',');
      int x = stoi(coords[1]);
      int y = getIndexFromLetter(coords[0]);
      if (x > xMax || y > yMax) {
        cout << "Invalid coordinate, try again. " << endl;
        goto label; // use this to restart the function
      }
      shots.push_back({ x, y });
    }
    return shots;
  }
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
      int remainder = n % 26;
      if (remainder == 0) {
         str += 'Z';
         n = (n / 26) - 1;
      }
      else {
         str += (remainder - 1) + 'A';
         n = n / 26;
      }
   }
   reverse(str.begin(), str.begin() + str.length());
   return str;
}
