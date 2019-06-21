#include "Program.hpp"

Program::Program(File input_file)
  : num_lines{0}, file{input_file}, total_size{0}, data_section{-1}, text_section{-1}
  {}

void Program::showTokenswithType() {
  cout << endl << "Printing Tokens and Types" << endl;
  for (unsigned int line = 0; line < tokens.size(); ++line) {
    for (auto token : tokens.at(line)) {
      cout << line << " Token-> " << token.tvalue << " value-> " << TokenTypeToString(token.type) << endl;
    }
  }
}

void Program::showTokens() {
  for (unsigned int line = 0; line < tokens.size(); ++line) {
    cout << line << " ";
    for (auto token : tokens.at(line)) {
      cout << token.tvalue << " ";
    }
    cout << endl;
  }
}
