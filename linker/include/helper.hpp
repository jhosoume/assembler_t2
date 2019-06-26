#ifndef HELPER
#define HELPER

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

#include "TokenType.hpp"
#include "SymbolData.hpp"

using ::std::string;
using ::std::vector;
using ::std::cout;
using ::std::endl;

class File {
public:
  File(char *);
  string fullname();
  string extension();
  string name();
private:
  std::string filename;
  std::string ext;
};

void helpMessage();
void invalidArgumentMessage();
vector<string> split(const string&, const string&);
File getFileNameFromArg(int, char **);
bool is_hex_notation(const string &);
bool is_integer_notation(const string &);
string TokenTypeToString(const TokenType &);
string SymbolTypeToString(const SymbolType &);

#endif
