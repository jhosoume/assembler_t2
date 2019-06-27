#include "InstructionTable.hpp"

InstructionTable::InstructionTable() {
  vector<TokenType> signature;

  // PUSH _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "PUSH", Instruction("PUSH", 2, 6, 0x68) ) );

  // POP __________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "POP", Instruction("POP", 2, 6, 0x58) ) );

  // CALL _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "CALL", Instruction("CALL", 1, 6, 0xE8) ) );

  // MOV __________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "MOV", Instruction("MOV", 2, 6, 0xA1) ) );

  // CDQ _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "CDQ", Instruction("CDQ", 0, 6, 0x99) ) );

  // IDIV __________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "IDIV", Instruction("IDIV", 1, 6, 0xF7) ) );

  // IMUL _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "IMUL", Instruction("IMUL", 2, 6, 0x0F) ) );

  // SUB _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "SUB", Instruction("SUB", 2, 6, 0x2B) ) );

  // CMP _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "CMP", Instruction("CMP", 2, 6, 0x83) ) );

  // JG _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "JG", Instruction("JG", 2, 6, 0x7F) ) );

  // INT _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "INT", Instruction("INT", 2, 6, 0xCD) ) );

  // ENTER _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "ENTER", Instruction("ENTER", 2, 6, 0xC8) ) );

  // LEAVE _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "LEAVE", Instruction("LEAVE", 2, 6, 0xC9) ) );

  // RET _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "RET", Instruction("RET", 2, 6, 0xC3) ) );

  // LOOP _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "LOOP", Instruction("LOOP", 2, 6, 0xE2) ) );

  // DEC _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "DEC", Instruction("DEC", 2, 6, 0x4E) ) );

  // JNE _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "JNE", Instruction("JNE", 2, 6, 0x75) ) );

  // JMP _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "JMP", Instruction("JMP", 2, 6, 0xEB) ) );

  // JGE _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "JGE", Instruction("JGE", 2, 6, 0x7D) ) );

  // SHL _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "SHL", Instruction("SHL", 2, 6, 0xC1) ) );

  // ADD _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "ADD", Instruction("ADD", 2, 6, 0x03) ) );

  // INC _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "INC", Instruction("INC", 2, 6, 0x40) ) );

  // NOT _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "NOT", Instruction("NOT", 2, 6, 0xF7) ) );

  // JL _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "JL", Instruction("JL", 2, 6, 0x7C) ) );

  // JE _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "JE", Instruction("JE", 2, 6, 0x74) ) );

  // JB _________________________________________________________
  instructions.insert(
    pair<string, Instruction>( "JB", Instruction("JB", 2, 6, 0x72) ) );
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
