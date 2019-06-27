#include "InstructionTable.hpp"

InstructionTable::InstructionTable() {
  vector<TokenType> signature;

  // PUSH _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "PUSH", Instruction("PUSH", 2, 6, 80) ) );

  // POP _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "POP", Instruction("POP", 2, 6, 80) ) );

  // CALL _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "CALL", Instruction("CALL", 1, 6, 232) ) );

  // MOV _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "MOV", Instruction("MOV", 2, 6, 163) ) );

}


// Print all possible signtures of all instructions
void InstructionTable::printInstructions() {
  for (const auto &pair_instruction : instructions) {
    Instruction instruction = pair_instruction.second;
    cout << "Instruction: " << instruction.name << endl;
    cout << "       Size: " << instruction.size << endl;
    cout << " Signatures: " << endl;
    for (auto signature : instruction.signatures) {
      cout << "       ";
      for (TokenType toktype : signature) {
        cout << TokenTypeToString(toktype) << " ";
      }
    cout << endl;
    }
  }
}

Instruction InstructionTable::get(const string &token_value) {
  return instructions.at(token_value);
}

Instruction InstructionTable::get(const Token &token) {
  return instructions.at(token.tvalue);
}

bool InstructionTable::isInstruction(const Token &token) {
  return isInstruction(token.tvalue);
}

bool InstructionTable::isInstruction(const string &token_value) {
  return (instructions.count(token_value) != 0);
}
