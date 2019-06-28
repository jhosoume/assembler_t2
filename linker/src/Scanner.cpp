#include "Scanner.hpp"

Scanner::Scanner(InstructionTable instructions, DirectiveTable directives, RegisterTable registers)
  : instruction_table{instructions}, directive_table{directives}, register_table{registers}
{
  const string tmp_letters = "ABCDEFGHIJKLMNOPQRSTUVXWYZ";
  const string tmp_numbers = "0123456789";
  const string tmp_specials = "_";
  for (auto character : tmp_letters) {
    validCharacters.insert(character);
    validFirstCharacters.insert(character);
  }
  for (auto character : tmp_numbers) {
    validCharacters.insert(character);
  }
  for (auto character : tmp_specials) {
    validCharacters.insert(character);
    validFirstCharacters.insert(character);
  }
  validFirstCharacters.insert('&');
}

// Receives a line and separates it into tokens, returning a vector of all
// the tokens in the line, classiying them and checking if they are valid
// PUT ALL OF THE TOKEN VALUES IN UPPERCASE
vector<Token> Scanner::splitIntoTokens(string line) {
  string delimiters = "\t   ";
  vector<Token> tokens;
  vector<string> line_words = split(line, delimiters);
  for (auto word : line_words) {
    std::transform(word.begin(), word.end(), word.begin(), ::toupper);
    tokens.push_back(Token(word, classifyToken(word), isTokenValid(word)));
  }
  return tokens;
}

// Function that groups up
bool Scanner::isTokenValid(string token) {
  return checkValidNumberOfChars(token) &
         checkIfAllCharactersAreValid(token) &
         checkIfSymbolStartsCorrectly(token);
}

// Classification of token accordingly to its content
TokenType Scanner::classifyToken(string token) {
  if (token.compare("") == 0) {
      return TokenType::EMPTY;
  } else if (token.compare(" ") == 0) {
      return TokenType::EMPTY;
  } else if (token.compare("\t") == 0) {
      return TokenType::EMPTY;
  } else if (token.compare("\n") == 0) {
      return TokenType::EMPTY;
  } else if (token.compare(" ") == 0) {
      return TokenType::EMPTY;
  } else if (token.compare(";") == 0) {
      return TokenType::COMMENT_SEMICOLON;
  } else if (token.compare(":") == 0) {
      return TokenType::LABEL_COLON;
  } else if (token.compare("+") == 0) {
      return TokenType::ADD_SYMBOL;
  } else if (token.compare("SECTION") == 0) {
      return TokenType::SECTION;
  } else if (token.compare("DATA") == 0) {
      return TokenType::DATA_SECTION;
  } else if (token.compare("TEXT") == 0) {
      return TokenType::TEXT_SECTION;
  } else if (token.compare("MACRO") == 0) {
      return TokenType::MACRO;
  } else if (token.compare("]") == 0) {
      return TokenType::CLOSE_BRACKET;
  } else if (token.compare("[") == 0) {
      return TokenType::OPEN_BRACKET;
  } else if ( (token.compare("END") == 0) || (token.compare("ENDMACRO") == 0) ) {
      return TokenType::ENDMACRO;
  } else if (token.compare(",") == 0) {
      return TokenType::COMMA_ARG_SEPARATOR;
  } else if (token.at(0) == '&') {
      return TokenType::MACRO_PARAMETER;
  } else if (instruction_table.instructions.count(token) > 0) {
      return TokenType::INSTRUCTION_TOKEN;
  } else if (directive_table.directives.count(token) > 0) {
      return TokenType::DIRECTIVE_TOKEN;
  } else if (register_table.registers.count(token) > 0) {
      return TokenType::REGISTER_TOKEN;
  } else if(checkIfDecNumber(token)) {
      return TokenType::NUMBER_DECIMAL;
  } else if(checkIfHexNumber(token)) {
      return TokenType::NUMBER_HEX;
  } else if(token.compare("80H") == 0) {
      return TokenType::END_HEX;
  } else if (!isTokenValid(token)) {
      return TokenType::INVALID;
  }
  return TokenType::SYMBOL;
}

bool Scanner::checkValidNumberOfChars(const string &token) {
  return token.size() <= 50;
}

bool Scanner::checkIfSymbolStartsCorrectly(const string &token) {
  const char firstChar = token.at(0);
  return (validFirstCharacters.find(firstChar) != validFirstCharacters.end());
}

bool Scanner::checkIfAllCharactersAreValid(const string &token) {
  bool valid = true;
  for (const char &character : token) {
    valid = valid && (validCharacters.find(character) != validCharacters.end());
  }
  return valid;
}

bool Scanner::checkIfDecNumber(const string &token) {
  return is_integer_notation(token);
}

//TODO Needs to add negative numbers
bool Scanner::checkIfHexNumber(const string &token) {
  return is_hex_notation(token);
}
