#ifndef TOKEN
#define TOKEN

#include <string>

#include "TokenType.hpp"

using ::std::string;


class Token {
public:
  Token(string, TokenType, bool);
  Token();
  string tvalue;
  TokenType type;
  bool valid;

  bool operator ==(const Token &);
};

#endif
