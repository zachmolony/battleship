#include <sstream>
#include <sys/stat.h>
#include <vector>

bool fileExists(const std::string& filename) {
  struct stat buffer{};
  bool fileExists = stat(filename.c_str(), &buffer) == 0; //check if the file exists
  return fileExists;
};

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> strings;
  std::stringstream sstream(s);
  std::string string;
  while(std::getline(sstream, string, delimiter)) {
    strings.push_back(string);
  }
  return strings;
}

//#endif // BATTLESHIPS__HELPERFUNCTIONS_H_
