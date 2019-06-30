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
  int value;
  int vec_size;
  SymbolType s_type = SymbolType::INSTRUCTION;
  bool text_section = true;
  bool data_section = false;
  vector <vector <Token> > operands;
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    if (text_section) {
      value = 0;
      vec_size = 0;
      s_type = SymbolType::INSTRUCTION;
      if (program.tokens.at(line).front().tvalue == "READCHAR") {
        symbol_table.addSymbol(line, program.tokens.at(line).front().tvalue, program_counter, s_type, value, vec_size);
        program.text_section = program_counter;
        program_counter = 0;
        text_section = false;
        continue;
      }
      if ( parser.hasLabel(program.tokens.at(line)) ) {
        // cout << "FOUND LABEL! " << program.tokens.at(line).front().tvalue << " | ";
        main_token = parser.getInstructionOrDirective(program.tokens.at(line));
        symbol_table.addSymbol(line, program.tokens.at(line).front().tvalue, program_counter, s_type, value, vec_size);
      }
      // if (program.tokens.at(line).front().tvalue == "")
      program_counter += parser.calculateSizeOfExpression(program.tokens.at(line), line);

    } else if (data_section) {
      operands = parser.groupOps(program.tokens.at(line));
      symbol_table.addSymbol(line, program.tokens.at(line).front().tvalue, program_counter, s_type, value, vec_size);
      program_counter += (operands.size() * 4);
    } else {
      if (program.tokens.at(line).front().tvalue == "SECTION" &&
          program.tokens.at(line).back().tvalue == ".DATA") {
        data_section = true;
      }
    }
  }
  symbol_table.listTable();
  return symbol_table;
}
