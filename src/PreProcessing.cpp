#include "PreProcessing.hpp"

PreProcessor::PreProcessor(const Scanner &scanner, const Parser &parser, Program &prog)
  : scanner{scanner}, parser{parser}, program{prog}
  {
    // Create set of all special characters that need spacing for token identification
    validSpecialCharacters.insert(';');
    validSpecialCharacters.insert('+');
    validSpecialCharacters.insert(':');
    validSpecialCharacters.insert(',');
  }

void PreProcessor::exec() {
  std::ifstream ifs(program.file.fullname());
  // Testing if file can be oppened
  if (!ifs.is_open()) {
    throw std::runtime_error("[ERR] " + program.file.fullname() + " could not be opened");
  }
  string line;
  string processed_line;
  unsigned int program_size = 0;
  vector<Token> tokens;
  // Used for verification if label is in a line before
  bool needs_concate = false;
  Token main_token;

  // Pre process each line individually
  while(std::getline(ifs, line)) {
    // Call function to remove all comentaries (all chars after ;)
    processed_line = removeComments(line);
    // Check if line is empty (all white spaces)
    if (processed_line.empty() ||
      std::all_of(processed_line.begin(), processed_line.end(),
        [](char c){
          return std::isspace(static_cast<unsigned char>(c));
      })) {
      continue;
    }
    // Add space between tokens to make process of separation easier
    processed_line = spaceTokens(processed_line);
    // Split line in tokens and get them all in uppercase
    tokens = scanner.splitIntoTokens(processed_line);
    // Check if last line parsed was just a label
    if (needs_concate) {
      // Concatenates with the last line
      program.tokens.back().insert(program.tokens.back().end(), tokens.begin(), tokens.end());
      needs_concate = false;
    } else {
      // If last line was not a lone label
      program.tokens.push_back(tokens);
      ++program_size;
    }
    if (tokens.back().type == TokenType::LABEL_COLON) {
      needs_concate = true;
    }

  }
  if (program_size != program.tokens.size()) {
    // cout << "Program counted: " << program_size << " Program size: " << program.tokens.size();
    throw std::runtime_error("[ERR] Program was not read correctly!");
  }
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    for (const auto &tok : program.tokens.at(line)) {
      if (tok.type == TokenType::INVALID) {
        cout << "[LEXICAL ERR] Line: " << line + 1 << " | Token '" << tok.tvalue << "' is not valid." << endl;
      }
    }
    parser.isExpressionValid(program.tokens.at(line), line);
    // Add label to equ_table
    main_token = parser.getInstructionOrDirective(program.tokens.at(line), line);
    if (main_token.type == TokenType::SECTION) {
      if (program.tokens.at(line).back().type == TokenType::DATA_SECTION) {
        text_mode = false;
        data_mode = true;
        if (program.data_section != -1) {
          cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Data section defined more than once." << endl;
        }
        program.data_section = line;
      } else if (program.tokens.at(line).back().type == TokenType::TEXT_SECTION) {
        data_mode = false;
        text_mode = true;
        if (program.text_section != -1) {
          cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Text section defined more than once." << endl;
        }
        program.text_section = line;
      } else {
        cout << "[SYNTAX ERR] Line: " << line + 1 << " | Invalid Section Defined." << endl;
      }
    }

    substEqu(line);
    parser.isExpressionValid(program.tokens.at(line), line);
    if (main_token.tvalue == "EQU") {
      if (text_mode || data_mode) {
        cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Equ definition is not outside sections;" << endl;
      }
      dealingWithEqu(line);
      --line;
    } else if (main_token.tvalue == "IF") {
      if (program.tokens.at(line).back().type == TokenType::NUMBER_DECIMAL ||
          program.tokens.at(line).back().type == TokenType::NUMBER_HEX) {
        // If the argument is 0: erase this line and the next
        if (std::stoi(program.tokens.at(line).back().tvalue) == 0) {
          program.tokens.erase(program.tokens.begin() + line);
          program.tokens.erase(program.tokens.begin() + line);
          --line;
        } else { // If the argument is not 0: erase this line
          program.tokens.erase(program.tokens.begin() + line);
          --line;
        }
      } else {
        cout << "[SEMANTIC ERR] Line: " << line + 1 << " | IF directive with invalid argument." << endl;
      }
    }
  }
  if (program.text_section < 0) {
    cout << "[SEMANTIC ERR] Text section was not defined." << endl;
  } else if (program.data_section < 0) {
    cout << "[SEMANTIC WARNING] Data section was not defined." << endl;
  } else if (program.data_section <= program.text_section) {
    cout << "[SEMANTIC ERR] Data section (Line: " << program.data_section + 1
      << ") is specified before text section (Line: " << program.text_section + 1 << ")." << endl;
  }
  // Macro is dealt last, because if the macro contains an EQU or IF it is already resolved
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    line = substMacro(line);
    main_token = parser.getInstructionOrDirectiveWithOut(program.tokens.at(line), line);
    if (main_token.type == TokenType::SECTION) {
      if (program.tokens.at(line).back().type == TokenType::DATA_SECTION) {
        text_mode = false;
        data_mode = true;
      } else if (program.tokens.at(line).back().type == TokenType::TEXT_SECTION) {
        data_mode = false;
        text_mode = true;
      }
    } else if (main_token.type == TokenType::INSTRUCTION_TOKEN) {
      if (data_mode || !text_mode) {
        cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Instruction outside text section;" << endl;
      }
    } else if (main_token.type == TokenType::DIRECTIVE_TOKEN) {
      if (!data_mode || text_mode) {
        cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Directive outside data section;" << endl;
      }
    } else if (main_token.tvalue == "MACRO") {
      if (!text_mode || data_mode) {
        cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Macro definition is not inside text section;" << endl;
      }
      if (!parser.hasLabel(program.tokens.at(line))) {
        cout << "[SYNTAX ERR] Line: " << line + 1 << " | Macro definition does not have a label." << endl;
      }
      dealingWithMacro(line);
      --line;
    }
  }
  // macro_table.printMacros();
}

// Creates separation of special characters from the rest of tokens to
// make split easier
string PreProcessor::spaceTokens(string line) {
  string new_line;
  for (char const &character : line) {
    if (validSpecialCharacters.find(character) != validSpecialCharacters.end()) {
      new_line.push_back(' ');
      new_line.push_back(character);
      new_line.push_back(' ');
    } else {
      new_line.push_back(character);
    }
  }
  return new_line;
}

// Remove comments from the rest of the line
string PreProcessor::removeComments(string line) {
  return line.substr(0, line.find(";"));
}

void PreProcessor::writePreProcessedFile() {
  std::ofstream preprocessed_file;
  preprocessed_file.open(program.file.name() + ".pre");
  for (const vector<Token> &line : program.tokens) {
    for (const Token &token : line) {
      preprocessed_file << token.tvalue << " ";
    }
    preprocessed_file << endl;
  }
  preprocessed_file.close();
}

void PreProcessor::dealingWithEqu(int line) {
  if (parser.hasLabel(program.tokens.at(line))) {
    if (equ_table.isEquDefined(program.tokens.at(line).front())) {
      cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Equ label already in use." << endl;
    } else {
      equ_table.addEqu(program.tokens.at(line).front(), program.tokens.at(line).back());
    }
  } else {
    cout << "[SYNTAX ERR] Line: " << line + 1 <<" | Missing label." << endl;
  }
  program.tokens.erase(program.tokens.begin() + line);
}

void PreProcessor::substEqu(int line) {
  // Redefines symbol acording to EQU
  for (unsigned int indx = 0; indx < program.tokens.at(line).size(); ++indx) {
    if (equ_table.isEquDefined(program.tokens.at(line).at(indx))) {
      program.tokens.at(line).at(indx) = equ_table.getEquToken(program.tokens.at(line).at(indx));
    }
  }
}

void PreProcessor::dealingWithMacro(int line) {
  Token main_token;
  bool found_end = false;
  string macro_name;
  int num_operands = 0;
  // Check if macro name is beign defined
  if (parser.hasLabel(program.tokens.at(line))) {
    // Check if the macro is being redefined
    if (macro_table.isMacroDefined(program.tokens.at(line).front())) {
      cout << "[SEMANTIC ERR] Line: " << line + 1 << " | Macro label already in use." << endl;
    } else {
      macro_name = program.tokens.at(line).front().tvalue;
      Macro macro = Macro(macro_name);
      // Body of the macro must be at the next line
      if ((line + 1) == program.tokens.size()) {
        cout << "[SYNTAX ERR] Line: " << line + 1 << " | Macro being defined in the last line." << endl;
      }
      // Get all operands
      for (const Token &token : program.tokens.at(line)) {
        if (token.type == TokenType::MACRO_PARAMETER) {
          ++num_operands;
          macro.addOperand(token.tvalue);
        }
      }
      // For each line until the end, increment
      for (unsigned int macro_line = (line + 1); macro_line < program.tokens.size(); ++macro_line) {
        main_token = parser.getInstructionOrDirective(program.tokens.at(macro_line), macro_line);
        if (main_token.type == TokenType::ENDMACRO) {
          found_end = true;
          program.tokens.erase(program.tokens.begin() + macro_line);
          break;
        }
        macro.macro_definition.push_back(program.tokens.at(macro_line));
        program.tokens.erase(program.tokens.begin() + macro_line);
        --macro_line;
      }
      if (!found_end) {
        cout << "[SYNTATIC ERROR] Macro does not have an end!" << endl;
      }
      macro_table.insert(macro_name, macro);
    }
  } else {
    cout << "[SYNTAX ERR] Line: " << line + 1 <<" | Missing label." << endl;
  }
  program.tokens.erase(program.tokens.begin() + line);
}

int PreProcessor::substMacro(int line) {
  // Redefines symbol acording to MACRO
  std::vector<int>::iterator it;
  vector <vector <Token>> macro_body;
  bool subst = false;
  Token tok;
  vector <Token> parameters;
  vector <Token> macro_line;
  Macro subst_macro;
  int operand_indx;
  if (macro_table.isMacroDefined(program.tokens.at(line).front())) {
    subst = true;
    subst_macro = macro_table.get(program.tokens.at(line).front().tvalue);
    for (unsigned int indx = 1; indx < program.tokens.at(line).size(); ++indx) {
      tok = program.tokens.at(line).at(indx);
      if (tok.type == TokenType::SYMBOL) {
        parameters.push_back(tok);
      }
    }
  }
  if (subst) {
    if (parameters.size() != subst_macro.getNumOperands()) {
      cout << "[SYNTAX ERR] Line: " << line + 1 << " | Invalid Number of Parameters. "
      << "Expected "<< subst_macro.getNumOperands() << ", received " << parameters.size() << endl;
    }
    for (int indx = 0; indx < subst_macro.macro_definition.size(); ++indx) {
      macro_line = subst_macro.macro_definition.at(indx);
      for (int token_indx = 0; token_indx < macro_line.size(); ++token_indx) {
        if (std::find(subst_macro.operands_names.begin(), subst_macro.operands_names.end(),
            macro_line.at(token_indx).tvalue) != subst_macro.operands_names.end()) {
          operand_indx = subst_macro.operandIndx(macro_line.at(token_indx));
          if (operand_indx < parameters.size()) {
            macro_line.at(token_indx) = parameters.at(operand_indx);
          } else {
            cout << "[SYNTAX ERR] Line: " << line + 1 << " | Specified less parameters than necessary for macro." << endl;
          }
        }
      }
      program.tokens.insert(program.tokens.begin() + line + 1 + indx, macro_line);
    }
    program.tokens.erase(program.tokens.begin() + line);
    --line;
  }
  return line;
}
