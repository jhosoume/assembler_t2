#include "assembler.hpp"

int main(int argc, char **argv) {
  InstructionTable instruction_table = InstructionTable();
  DirectiveTable directive_table = DirectiveTable();
  Scanner scanner = Scanner(instruction_table, directive_table);
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
  // prog.showTokens();
  zero_run.writePreProcessedFile();
  FirstPass first_pass = FirstPass(parser, prog, instruction_table, directive_table);
  cout << "**********************" << endl;
  cout << "Finish First Pass" << endl;
  cout << "**********************" << endl << endl;
  SymbolTable symbol_table = first_pass.exec();
  SecondPass second_pass = SecondPass(parser,
                                      prog,
                                      symbol_table,
                                      instruction_table,
                                      directive_table);
  // prog.showTokens();
  second_pass.exec();
  second_pass.writeObjectFile();
  cout << "**********************" << endl;
  cout << "Finish Second Pass" << endl;
  cout << "**********************" << endl << endl;
  return 0;
}
