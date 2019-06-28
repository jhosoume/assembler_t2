#include "helper.hpp"

void helpMessage() {
  std::cout <<  "Usage: tradutor FILE..." << std::endl;
  std::cout <<  "Assembles FILE into a pre-processed text file (.pre) with the same \
    name as the original file and an object text file (.obj). All files will be \
    saved in the current directory." << std::endl;
}

void noFileMessage() {
  std::cout << "[ERR] FILE was not specified. Must be path plus filename and its extension." << std::endl;
}
void invalidArgumentMessage() {
  std::cout << "[ERR] FILE was not correctly specified." << std::endl;
}

File::File(char *file) {
  // Separates filename from its extension
  bool ext_bool = false;
  for (unsigned int indx = 0; indx < strlen(file); ++indx) {
    if (file[indx] == '.') {
      ext_bool = true;
      continue;
    }
    ext_bool ? ext.push_back(file[indx]) :
               filename.push_back(file[indx]);
  }
}

string File::fullname() {
  return (ext.empty() ? filename : (filename + '.' + ext));
}

string File::extension() {
  return ext;
}

string File::name() {
  return filename;
}

// Returns a File type that has the filename and its extension
File getFileNameFromArg(int argc, char **argv) {
  // Check if number of inputs is correct, should have one argument
  if (argc < 2) {
    noFileMessage();
    helpMessage();
    exit(1);
  } else if (argc > 2) {
    invalidArgumentMessage();
    helpMessage();
    exit(1);
  }
  File file = File(argv[1]);
  return file;
}

// Split string into tokens according to delimiters
vector<string> split(const string& str, const string& delim) {
  vector<string> parts;
  size_t start, end = 0;
  while (end < str.size()) {
    start = end;
    while (start < str.size() && (delim.find(str[start]) != string::npos)) {
      ++start;  // skip initial whitespace
    }
    end = start;
    while (end < str.size() && (delim.find(str[end]) == string::npos)) {
      ++end; // skip to end of word
    }
    if (end - start != 0) {  // just ignore zero-length strings.
      parts.push_back(string(str, start, end - start));
    }
  }
  return parts;
}

// Verify if the string is a valid hex (positive or negative)
bool is_hex_notation(const string &s) {
  return ((s.size() > 2 &&
          s.compare(0, 2, "0X") == 0 &&
          s.find_first_not_of("0123456789abcdefABCDEF", 2) == string::npos)
      ||(s.size() > 3 &&
        s.compare(0, 3, "-0X") == 0 &&
        s.find_first_not_of("0123456789abcdefABCDEF", 3) == string::npos));
}

bool is_integer_notation(const string &s) {
  string tmp_s = s;
  if (tmp_s.at(0) == '-')
    tmp_s.erase(0, 1);
  return std::find_if(tmp_s.begin(), tmp_s.end(),
    [](const char &character) {
        return !std::isdigit(character);
    }) == tmp_s.end();

}

// Helper function to aux the verification of token types
string TokenTypeToString(const TokenType &type) {
  switch(type) {
    case TokenType::INVALID :
      return "INVALID";
      break;
    case TokenType::NUMBER_DECIMAL :
      return "NUMBER_DECIMAL";
      break;
    case TokenType::NUMBER_HEX :
      return "NUMBER_HEX";
      break;
    case TokenType::SYMBOL :
      return "SYMBOL";
      break;
    case TokenType::LABEL_COLON :
      return "LABEL_COLON";
      break;
    case TokenType::MACRO :
      return "MACRO";
      break;
    case TokenType::DIRECTIVE_TOKEN :
      return "DIRECTIVE";
      break;
    case TokenType::INSTRUCTION_TOKEN :
      return "INSTRUCTION";
      break;
    case TokenType::REGISTER_TOKEN :
      return "REGISTER";
      break;
    case TokenType::COMMENT_SEMICOLON:
      return "COMMENT_SEMICOLON";
      break;
    case TokenType::COMMA_ARG_SEPARATOR:
      return "COMMA_ARG_SEPARATOR";
      break;
    case TokenType::MACRO_PARAMETER:
      return "MACRO_PARAMETER";
      break;
    case TokenType::ENDMACRO:
      return "ENDMACRO";
      break;
    case TokenType::SECTION:
      return "SECTION";
      break;
    case TokenType::DATA_SECTION:
      return "DATA_SECTION";
      break;
    case TokenType::TEXT_SECTION:
      return "TEXT_SECTION";
      break;
    case TokenType::ADD_SYMBOL:
      return "ADD_SYMBOL";
      break;
    case TokenType::OPEN_BRACKET:
      return "OPEN_BRACKET";
      break;
    case TokenType::CLOSE_BRACKET:
      return "CLOSE_BRACKET";
      break;
    case TokenType::END_HEX:
      return "END_HEX";
      break;
    default:
      return "UNKNOWN_TYPE";
      break;
  }
}

string SymbolTypeToString(const SymbolType &type) {
  switch(type) {
    case SymbolType::CONST:
      return "CONST";
      break;
    case SymbolType::SPACE:
      return "SPACE";
      break;
    case SymbolType::INSTRUCTION:
      return "INSTRUCTION";
      break;
    default:
      return "UNKNOWN_TYPE";
      break;
  }
}

int bigToLittle(const int &num) {
  int swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
                ((num<<8)&0xff0000) | // move byte 1 to byte 2
                ((num>>8)&0xff00) | // move byte 2 to byte 1
                ((num<<24)&0xff000000); // byte 0 to byte 3
  return swapped;
}
