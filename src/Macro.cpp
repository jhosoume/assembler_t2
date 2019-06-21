#include "Macro.hpp"
Macro::Macro() {}

Macro::Macro(string name)
  : name{name} {}

int Macro::getNumOperands() {
  return operands_names.size();
}

void Macro::addOperand(string name) {
  operands_names.push_back(name);
}

int Macro::operandIndx(Token tok) {
  return operandIndx(tok.tvalue);
}

int Macro::operandIndx(string op_name) {
  int indx = 0;
  for (indx = 0; indx < operands_names.size(); ++indx) {
    if (op_name == operands_names.at(indx)) {
      return indx;
    }
  }
  return indx;
}

void Macro::addOperandPosition(string name, int line, int indx) {
  Position macro_position;
  macro_position.line = line; macro_position.indx = indx;
  operands_positions[name].push_back(macro_position);
}

void Macro::addMacroLines(vector<Token> line_tokens) {
  macro_definition.push_back(line_tokens);
}
