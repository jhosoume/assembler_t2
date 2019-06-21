#include "InstructionTable.hpp"

InstructionTable::InstructionTable() {
  vector<TokenType> signature;

  // ADD _________________________________________________________
  instructions.insert( pair<string, Instruction>( "ADD", Instruction("ADD", 1, 1) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("ADD").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("ADD").signatures.push_back(signature);
  signature.clear();

  // SUB _________________________________________________________
  instructions.insert( pair<string, Instruction>( "SUB", Instruction("SUB", 1, 2) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("SUB").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("SUB").signatures.push_back(signature);
  signature.clear();

  // MULT _________________________________________________________
  instructions.insert( pair<string, Instruction>( "MULT", Instruction("MULT", 1, 3) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("MULT").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("MULT").signatures.push_back(signature);
  signature.clear();

  // DIV _________________________________________________________
  instructions.insert( pair<string, Instruction>( "DIV", Instruction("DIV", 1, 4) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("DIV").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("DIV").signatures.push_back(signature);
  signature.clear();

  // JMP _________________________________________________________
  instructions.insert( pair<string, Instruction>( "JMP", Instruction("JMP", 1, 5) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("JMP").signatures.push_back(signature);
  signature.clear();

  // JMPN _________________________________________________________
  instructions.insert( pair<string, Instruction>( "JMPN", Instruction("JMPN", 1, 6) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("JMPN").signatures.push_back(signature);
  signature.clear();

  // JMPP _________________________________________________________
  instructions.insert( pair<string, Instruction>( "JMPP", Instruction("JMPP", 1, 7) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("JMPP").signatures.push_back(signature);
  signature.clear();

  // JMPZ _________________________________________________________
  instructions.insert( pair<string, Instruction>( "JMPZ", Instruction("JMPZ", 1, 8) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("JMPZ").signatures.push_back(signature);
  signature.clear();

  // COPY _________________________________________________________
  instructions.insert( pair<string, Instruction>( "COPY", Instruction("COPY", 2, 9) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN); //CASO 1
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::COMMA_ARG_SEPARATOR);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("COPY").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);//CASO 2
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::COMMA_ARG_SEPARATOR);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("COPY").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);//CASO 3
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  signature.push_back(TokenType::COMMA_ARG_SEPARATOR);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("COPY").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);//CASO 4
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  signature.push_back(TokenType::COMMA_ARG_SEPARATOR);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("COPY").signatures.push_back(signature);
  signature.clear();

  // LOAD _________________________________________________________
  instructions.insert( pair<string, Instruction>( "LOAD", Instruction("LOAD", 1, 10) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("LOAD").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("LOAD").signatures.push_back(signature);
  signature.clear();

  // STORE _________________________________________________________
  instructions.insert( pair<string, Instruction>( "STORE", Instruction("STORE", 1, 11) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("STORE").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("STORE").signatures.push_back(signature);
  signature.clear();

  // INPUT _________________________________________________________
  instructions.insert( pair<string, Instruction>( "INPUT", Instruction("INPUT", 1, 12) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("INPUT").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("INPUT").signatures.push_back(signature);
  signature.clear();

  // OUTPUT _________________________________________________________
  instructions.insert( pair<string, Instruction>( "OUTPUT", Instruction("OUTPUT", 1, 13) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  instructions.at("OUTPUT").signatures.push_back(signature);
  signature.clear();
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  signature.push_back(TokenType::SYMBOL);
  signature.push_back(TokenType::ADD_SYMBOL);
  signature.push_back(TokenType::NUMBER_DECIMAL);
  instructions.at("OUTPUT").signatures.push_back(signature);
  signature.clear();

  // STOP  _________________________________________________________
  instructions.insert( pair<string, Instruction>( "STOP", Instruction("STOP", 0, 14) ) );
  signature.push_back(TokenType::INSTRUCTION_TOKEN);
  instructions.at("STOP").signatures.push_back(signature);
  signature.clear();
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
