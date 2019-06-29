#include "SecondPass.hpp"

SecondPass::SecondPass(const Parser &parser,
                       const Program &prog,
                       const SymbolTable &sbt,
                       const InstructionTable &inst_table,
                       const DirectiveTable &dir_table,
                       const RegisterTable &reg_table
                      )
  : parser{parser}, program{prog}, symbol_table{sbt}, instruction_table{inst_table},
    directive_table{dir_table}, register_table{reg_table}
  {}

void SecondPass::exec() {
  // Open file for writing the object file
  vector<Token> tokens;
  vector < vector<Token> > operands;
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    // cout << line << " ";
    tokens = program.tokens.at(line);
    // Not consider labels
    if (parser.hasLabel(tokens)) {
      // If has label, put iterator after label
      tokens.assign(tokens.begin() + 2, tokens.end());
    }
    parser.checkDerivation(tokens, line);
    if (tokens.front().type == TokenType::INSTRUCTION_TOKEN) {
      // If instruction, needs to add opcode then deal with operands
      exec_code.push_back(instruction_table.get(tokens.at(0)).op_code);
      // cout << exec_code.back() << " ";
      operands = parser.groupOps(program.tokens.at(line));
      if (operands.size() > 0) {
        for (const auto &operand : operands) {
          exec_code.push_back(getAddrValueFromOperand(operand, line));
          // cout << exec_code.back() << " ";
        }
      }
      if ((tokens.front().tvalue == "JMP") ||
          (tokens.front().tvalue == "JMPN") ||
          (tokens.front().tvalue == "JMPP") ||
          (tokens.front().tvalue == "JMPZ")
         ) {
        // TODO Make a try excepetion in case not found in table
        try {
          SymbolData data = symbol_table.getSymbolData(tokens.back().tvalue);
          if (data.symbol_type != SymbolType::INSTRUCTION) {
            cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Jump to invalid location!" << endl;
          }
        } catch(const std::out_of_range &e) {
          cout << "[SEMANTIC ERR | Line: " << line + 1 << "] Symbol '" << tokens.back().tvalue
            << "' could not be found in the Symbol Table" << endl;
        }
      } else if (tokens.front().type == TokenType::INSTRUCTION_TOKEN) {
        for (const auto &operand : operands) {
          try {
            SymbolData data = symbol_table.getSymbolData(operand.front().tvalue);
            if (data.symbol_type == SymbolType::INSTRUCTION) {
              cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Argument is invalid!"
                << " It should be a label to CONST or SPACE." << endl;
            }
          } catch(const std::out_of_range &e) {
            cout << "[SEMANTIC ERR | Line: " << line + 1 << "] Symbol '" << tokens.back().tvalue
              << "' could not be found in the Symbol Table" << endl;
          }
        }
      }
      if (tokens.front().tvalue == "DIV") {
        try {
          SymbolData data = symbol_table.getSymbolData(operands.front().front().tvalue);
          if ((data.value == 0) && (data.symbol_type == SymbolType::CONST)){
            cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Division by zero!" << endl;
          }
        } catch(const std::out_of_range &e) {
          cout << "[SEMANTIC ERR | Line: " << line + 1 << "] Symbol '" << tokens.back().tvalue
            << "' could not be found in the Symbol Table" << endl;
        }
      } else if (tokens.front().tvalue == "COPY") {
        try {
          SymbolData data = symbol_table.getSymbolData(operands.back().front().tvalue);
          if (data.symbol_type == SymbolType::CONST) {
            cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Modifying const data!" << endl;
          }
        } catch(const std::out_of_range &e) {
          cout << "[SEMANTIC ERR | Line: " << line + 1 << "] Symbol '" << operands.back().front().tvalue
            << "' could not be found in the Symbol Table" << endl;
        }
      } else if (tokens.front().tvalue == "STORE" || tokens.front().tvalue == "INPUT") {
        try {
          SymbolData data = symbol_table.getSymbolData(operands.front().front().tvalue);
          if (data.symbol_type == SymbolType::CONST) {
            cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Modifying const data!" << endl;
          }
        } catch(const std::out_of_range &e) {
          cout << "[SEMANTIC ERR | Line: " << line + 1 << "] Symbol '" << operands.back().front().tvalue
            << "' could not be found in the Symbol Table" << endl;
        }
      }
      // Check if has sum in line (Add in parse)
    } else if (tokens.at(0).tvalue == "CONST") {
      // If const, only add number to be in memory
      // TODO needs to deal with hex
      try {
        if (tokens.back().type == TokenType::NUMBER_DECIMAL) {
          exec_code.push_back(std::stoi( tokens.back().tvalue) );
        } else if (tokens.back().type == TokenType::NUMBER_HEX) {
          exec_code.push_back( std::stoi(tokens.back().tvalue, nullptr, 16) );
        } else {
          cout << "[ERR | Line " << line + 1 << "] Could not convert " << tokens.back().tvalue << endl;
        }
      } catch(const std::invalid_argument &e) {
        cout << "[ERR | Line " << line + 1 << "] Could not convert " << tokens.back().tvalue << endl;
      }
      // cout << exec_code.back() << " ";
    } else if (tokens.at(0).tvalue == "SPACE") {
      // If space, add zeros to memory
      if (tokens.back().type == TokenType::NUMBER_DECIMAL) {
        for (int num_zeros = 0; num_zeros < std::stoi(tokens.back().tvalue); ++num_zeros) {
          exec_code.push_back(0);
          // cout << exec_code.back() << " ";
        }
      } else {
        exec_code.push_back(0);
        // cout << exec_code.back() << " ";
      }
    }
    // cout << endl;
  }
}

void SecondPass::writeObjectFile() {
  std::ofstream object_file;
  object_file.open(program.file.name() + ".obj");
  for (auto code : exec_code) {
    object_file << code << " ";
  }
  object_file.close();
}

void SecondPass::showObjectCode() {
    for (auto code : exec_code) {
      cout << code << " ";
    }
    cout << endl;
}

int SecondPass::getAddrValueFromOperand(vector <Token> operand, int line) {
  try {
    int addr = symbol_table.getSymbolAddress(operand.at(0));
    int addition = 0;
    int offset = symbol_table.getSymbolOffset(operand.at(0));
    if (operand.size() > 1) {
      // TODO move conversion of string to number to the token class
      // TODO check if hex
      if (operand.back().type == TokenType::NUMBER_HEX) {
        addition = std::stoi(operand.back().tvalue, nullptr, 16);
      } else if (operand.back().type == TokenType::NUMBER_DECIMAL) {
        addition = std::stoi(operand.back().tvalue);
      } else {
        addition = std::stoi(operand.back().tvalue);
      }

      if (addition >= offset) {
        cout << "[SEMANTIC ERR | Line " << line + 1 << "] Array operand (+ " << addition
          << ") out of bounds (limit: " << offset << ")." << endl;
      }
    }
    return addr + addition;
  } catch(const std::out_of_range &e) {
    cout << "[SEMANTIC ERR | Line " << line + 1 << "] Operand " << operand.at(0).tvalue << " not found in the Symbols Table." << endl;
    return -1;
  } catch(const std::invalid_argument &e) {
    cout << "[ERR | Line " << line + 1 << "] Could not convert " << operand.back().tvalue << endl;
    return -1;
  }
}
