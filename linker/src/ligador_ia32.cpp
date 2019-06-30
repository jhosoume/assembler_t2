#include "assembler.hpp"

int main(int argc, char **argv) {
  InstructionTable instruction_table = InstructionTable();
  DirectiveTable directive_table = DirectiveTable();
  RegisterTable register_table = RegisterTable();
  Scanner scanner = Scanner(instruction_table, directive_table, register_table);
  Parser parser = Parser(instruction_table, directive_table);
  // Get file to be assembled
  File input_file = getFileNameFromArg(argc, argv);

  Program prog = Program(input_file);
  PreProcessor zero_run = PreProcessor(scanner, parser, prog);
  // instruction_table.printInstructions();
  // directive_table.printDirectives();
  zero_run.exec();
  cout << "**********************" << endl;
  cout << "Finish Pre Processment" << endl;
  cout << "**********************" << endl << endl;
  prog.showTokenswithType();
  zero_run.writePreProcessedFile();
  FirstPass first_pass = FirstPass(parser, prog, instruction_table,
                                   directive_table, register_table);
  SymbolTable symbol_table = first_pass.exec();
  cout << "**********************" << endl;
  cout << "Finish First Pass" << endl;
  cout << "**********************" << endl << endl;
  SecondPass second_pass = SecondPass(parser,
                                      prog,
                                      symbol_table,
                                      instruction_table,
                                      directive_table,
                                      register_table);
  // // // prog.showTokens();
  second_pass.exec();
  // // second_pass.writeObjectFile();
  // Translate translator =  Translate(parser,
  //                                   prog);
  // translator.exec();
  // translator.writeNasmFile();
  // cout << "**********************" << endl;
  // cout << "Finish Translation" << endl;
  // cout << "**********************" << endl << endl;
  return 0;
}
