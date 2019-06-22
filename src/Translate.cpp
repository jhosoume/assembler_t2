#include "Translate.hpp"

Translate::Translate(const Parser &parser,
                     const Program &prog
                    )
  : parser{parser}, program{prog}
  {}

void Translate::exec() {
  vector<Token> tokens;
  vector < vector<Token> > operands;
  string aux_string;
  nasm_code.push_back("global _start\n");
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    cout << line << " | ";
    tokens = program.tokens.at(line);

    // ADDING LABEL
    if (parser.hasLabel(tokens)) {
      // If has label, put iterator after label
      nasm_code.push_back(tokens.front().tvalue + ":\n");
      tokens.assign(tokens.begin() + 2, tokens.end());
      // Add label
    }

    // DEALING WITH SECTION
    if (tokens.front().type == TokenType::SECTION) {
      nasm_code.push_back("section ");
      if (tokens.back().type == TokenType::DATA_SECTION) {
        nasm_code.back() = nasm_code.back() + ".data\n";
      } else if (tokens.back().type == TokenType::TEXT_SECTION) {
        nasm_code.back() = nasm_code.back() + ".text\n";
        nasm_code.push_back("_start: \n");
      }
      // DEALING WITH INPUT
    } else if (tokens.front().tvalue == "INPUT") {
      nasm_code.push_back("call ReadInteger\n");
      aux_string = "mov eax, [";
      aux_string = aux_string + tokens.back().tvalue + "]\n";
      nasm_code.push_back(aux_string);
    }





    for (const auto token : tokens) {
      cout << token.tvalue << " ";
    }
    cout << endl;
  }
  showNasmCode();
}

void Translate::writeNasmFile() {
  std::ofstream nasm_file;
  nasm_file.open(program.file.name() + ".s");
  for (auto code : nasm_code) {
    nasm_file << code << " ";
  }
  nasm_file.close();
}

void Translate::showNasmCode() {
  cout << endl << "***********" << endl;
  cout << "NASM Code" << endl << endl;
    for (auto code : nasm_code) {
      cout << code;
    }
  cout << "***********" << endl;
    cout << endl;
}
