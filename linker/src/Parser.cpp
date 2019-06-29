#include "Parser.hpp"

Parser::Parser(const InstructionTable &inst_t, const DirectiveTable &dir_t)
  : instruction_table{inst_t}, directive_table{dir_t}
{}

// Make sintatic analysis of a line of tokens (Expression)
bool Parser::isExpressionValid(const vector<Token> &tokens, int line) {
  return checkLabelValid(tokens, line);
}

bool Parser::checkDerivation(const vector<Token> &tokens, int line) {
  Token main_tok;
  vector<TokenType> types;
  for (auto indx = 0; indx < tokens.size(); ++indx) {
    types.push_back(tokens.at(indx).type);
  }
  if (tokens.front().type == TokenType::DIRECTIVE_TOKEN) {
    for (const auto &signature : directive_table.get(tokens.front()).signatures) {
      if (types == signature) {
        return true;
      }
    }
    // if (std::find(directive_table.get(tokens.front()).signatures.begin(),
    //               directive_table.get(tokens.front()).signatures.end(),
    //               types) != directive_table.get(tokens.front()).signatures.end()) {
    //   return true;
    // } else {
    // }
    cout << "[SYNTAX ERR] Line: " << line + 1 << " Directive with incorrect signature" << endl;

  } else if (tokens.front().type == TokenType::INSTRUCTION_TOKEN) {
    for (const auto &signature : instruction_table.get(tokens.front()).signatures) {
      if (types == signature) {
        return true;
      }
    }
    cout << "[SYNTAX ERR] Line: " << line + 1 << " Instruction '" << tokens.front().tvalue
      << "' with incorrect arguments or one token may be invalid" << endl;
  }
  return false;
}

bool Parser::checkLabelValid(const vector <Token> &tokens, int line) {
  int num_labels = 0;
  for (unsigned int token_indx = 0; token_indx < tokens.size(); ++token_indx) {
    if (tokens.at(token_indx).type == TokenType::LABEL_COLON) {
      ++num_labels;
      // Verifies if colon has a symbol defining a label before
      if (token_indx <= 0 ||
          tokens.at(token_indx - 1).type != TokenType::SYMBOL) {
            cout << "[SYNTAX ERR | Line " << line + 1 << "] Colon is not accompanied by a proper label!" << endl;
            return false;
      }
    }
  }
  // Only valid if there is one or none labels
  bool result = num_labels < 1;
  if (num_labels > 1)
    cout << "[SYNTAX ERR | Line " << line + 1 << "] Expression has more than one label!" << endl;
  return result;
}

bool Parser::hasLabel(const vector <Token> &tokens) {
  for (const Token &token : tokens) {
    if (token.type == TokenType::LABEL_COLON) {
      return true;
    }
  }
  return false;
}

// Get the main token of the expression. All expressions needs a directive
// or an instruction
Token Parser::getInstructionOrDirectiveWithOut(const vector<Token> &tokens, int line) {
  int num_dir_or_inst = 0;
  Token dir_or_inst;
  for (const Token &token : tokens) {
    if (token.type == TokenType::INSTRUCTION_TOKEN ||
        token.type == TokenType::DIRECTIVE_TOKEN   ||
        token.type == TokenType::SECTION           ||
        token.type == TokenType::MACRO             ||
        token.type == TokenType::ENDMACRO
    ) {
      ++num_dir_or_inst;
      dir_or_inst = token;
    }
  }
  if (num_dir_or_inst > 1) {
    cout << "[SYNTAX ERR | Line " << line + 1 << "] Line with more than one instruction or directive!" << endl;
  } else if (num_dir_or_inst <= 0) {
    cout << "[SYNTAX ERR | Line " << line + 1 << "] Line does not have a directive or an instruction!" << endl;
    cout << "[ERR " << line + 1 <<  "] Tokens found: ";
    for (const Token &token : tokens) {
      cout << token.tvalue;
    }
    cout << endl;
  }
  return dir_or_inst;
}

Token Parser::getInstructionOrDirective(const vector<Token> &tokens, int line) {
  int num_dir_or_inst = 0;
  Token dir_or_inst;
  for (const Token &token : tokens) {
    if (token.type == TokenType::INSTRUCTION_TOKEN ||
        token.type == TokenType::DIRECTIVE_TOKEN   ||
        token.type == TokenType::SECTION           ||
        token.type == TokenType::MACRO             ||
        token.type == TokenType::ENDMACRO
    ) {
      ++num_dir_or_inst;
      dir_or_inst = token;
    }
  }
  return dir_or_inst;
}

// Function to calculate the total size of the instruction or directive
int Parser::calculateSizeOfExpression(const vector<Token> &tokens, int line) {
  int size = 0;
  Token dir_inst_token = getInstructionOrDirective(tokens, line);
  // All instructions have a defined size
  if (dir_inst_token.type == TokenType::INSTRUCTION_TOKEN) {
    return instruction_table.get(dir_inst_token).size;
    // Some directives have a variable size
  } else if (dir_inst_token.type == TokenType::DIRECTIVE_TOKEN) {
    size = directive_table.get(dir_inst_token).size;
    // If the directive is a space, it depends on the allocated size
    return size;
  } else if (dir_inst_token.type == TokenType::SECTION) {
    return 0;
  } else {
    return 0;
  }
}

int Parser::hasSumInLine(const vector<Token> &tokens) {
  int num_sums = 0;
  for (const Token &token : tokens) {
    if (token.type == TokenType::ADD_SYMBOL) {
      ++num_sums;
    }
  }
  return num_sums;
}


vector<vector<Token>> Parser::groupOps(const vector<Token> &tokens) {
  vector< vector<Token> > operands;
  vector<Token> operand;
  size_t indx = 0;
    // Ignore label
  while (indx < tokens.size() &&
          (tokens.at(indx).type != TokenType::INSTRUCTION_TOKEN &&
           tokens.at(indx).type != TokenType::DIRECTIVE_TOKEN)) {
    ++indx;
  }
  // Skip Instruction or Directive
  ++indx;
  while (indx < tokens.size()) {
    // Stop only if find comma separator
    while (indx < tokens.size() && tokens.at(indx).type != TokenType::COMMA_ARG_SEPARATOR) {
      operand.push_back(tokens.at(indx));
      // cout << "tk" << indx << ": " << operand.back().tvalue << " ";
      ++indx;
    }
    ++indx;;
    // Does not include group of operands if it is empty
    if (operand.size() > 0) {
      operands.push_back(operand);
    }
    operand.clear();
  }
  return operands;
}
