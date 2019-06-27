#include "RegisterTable.hpp"

RegisterTable::RegisterTable() {
  // EAX _________________________________________________________
  registers.insert(
    pair<string, Register>( "EAX", Register("EAX", 0) ) );

  // EBX _________________________________________________________
  registers.insert(
    pair<string, Register>( "EBX", Register("EBX", 1) ) );

  // ECX _________________________________________________________
  registers.insert(
    pair<string, Register>( "ECX", Register("ECX", 2) ) );

  // EDX _________________________________________________________
  registers.insert(
    pair<string, Register>( "EDX", Register("EDX", 3) ) );

  // ESP _________________________________________________________
  registers.insert(
    pair<string, Register>( "ESP", Register("ESP", 4) ) );

  // EBP _________________________________________________________
  registers.insert(
    pair<string, Register>( "EBP", Register("EBP", 5) ) );

  // ESI _________________________________________________________
  registers.insert(
    pair<string, Register>( "ESI", Register("ESI", 6) ) );

  // EDI _________________________________________________________
  registers.insert(
    pair<string, Register>( "EDI", Register("EDI", 7) ) );
}


// Print all possible signtures of all registers
void RegisterTable::printRegisters() {
  for (const auto &pair_register : registers) {
    Register reg = pair_register.second;
    cout << "Register: " << reg.name << endl;
    cout << "       Size: " << reg.op_code << endl;
    cout << endl;
  }
}

Register RegisterTable::get(const string &token_value) {
  return registers.at(token_value);
}

Register RegisterTable::get(const Token &token) {
  return registers.at(token.tvalue);
}

bool RegisterTable::isRegister(const Token &token) {
  return isRegister(token.tvalue);
}

bool RegisterTable::isRegister(const string &token_value) {
  return (registers.count(token_value) != 0);
}
