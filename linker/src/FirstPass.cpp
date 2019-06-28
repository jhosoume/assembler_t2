#include "FirstPass.hpp"

FirstPass::FirstPass(const Parser &parser,
                     const Program &prog,
                     const InstructionTable &inst_table,
                     const DirectiveTable &dir_table,
                     const RegisterTable &reg_table
                   )
  : parser{parser}, program{prog}, instruction_table{inst_table},
    directive_table{dir_table}, register_table{reg_table}
  {}

SymbolTable FirstPass::exec() {
  SymbolTable symbol_table = SymbolTable();
  int program_counter = 0;
  Token main_token;
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    int value = 0;
    int vec_size = 0;
    SymbolType s_type = SymbolType::INSTRUCTION;
    cout << line << " ";
    if ( parser.hasLabel(program.tokens.at(line)) ) {
      cout << "FOUND LABEL! " << program.tokens.at(line).front().tvalue << " | ";

      main_token = parser.getInstructionOrDirective(program.tokens.at(line));
      symbol_table.addSymbol(line, program.tokens.at(line).front().tvalue, program_counter, s_type, value, vec_size);
    }
    program_counter += 6;
    cout << endl;
  }
  symbol_table.listTable();
  program.total_size = program_counter;
  return symbol_table;
}
