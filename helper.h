#include <sstream>
#include <sys/stat.h>
#include <vector>

#ifndef BATTLESHIPS__HELPERFUNCTIONS_H_
#define BATTLESHIPS__HELPERFUNCTIONS_H_


using namespace std;


bool fileExists(const string& filename);

vector<string> split(const string &s, char delimiter) {
  vector<string> strings;
  stringstream sstream(s);
  string string;
  while(getline(sstream, string, delimiter)) {
    strings.push_back(string);
  }
  return strings;
}

#endif // BATTLESHIPS__HELPERFUNCTIONS_H_
