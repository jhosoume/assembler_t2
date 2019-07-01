#include "SecondPass.hpp"

int convertChar(char bar) {
    if ( (int) bar < 58) {
      return (int) bar - 48;
    } else {
      return (int) bar - 87;
    }
}

struct HexCharStruct {
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o,
                                const HexCharStruct& hs) {
  return ( o << std::hex << (int) hs.c );
}

inline HexCharStruct hex(unsigned char _c) {
  return HexCharStruct(_c);
}


SecondPass::SecondPass(const Parser &parser,
                       const Program &prog,
                       const SymbolTable &sbt,
                       const InstructionTable &inst_table,
                       const DirectiveTable &dir_table,
                       const RegisterTable &reg_table
                      )
  : parser{parser}, program{prog}, symbol_table{sbt}, instruction_table{inst_table},
    directive_table{dir_table}, register_table{reg_table}
  {}

void SecondPass::exec() {
  // Open file for writing the object file
  vector<Token> tokens;
  vector<Token> tokens_no_dword;
  vector < vector<Token> > operands;
  bool text_section = true;
  bool data_section = false;
  int location;
  char bytes[4];
  int program_counter = 0;
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    // cout << line << " ";
    tokens = program.tokens.at(line);
    // Not consider labels
    if (parser.hasLabel(tokens)) {
      // If has label, put iterator after label
      tokens.assign(tokens.begin() + 2, tokens.end());
    }
    if (text_section) {
      program_counter += parser.calculateSizeOfExpression(program.tokens.at(line), line);
      cout << "PC = " << program_counter << " INST: " << program.tokens.at(line).front().tvalue << endl;
      if (program.tokens.at(line).front().tvalue == "READCHAR") {
        text_section = false;
        continue;
      }
      operands = parser.groupOps(program.tokens.at(line));
      // cout << "OPERANDS: ";
      // for (auto op : operands) {
      //   cout << stringfyOps(op);
      //   cout <<  " | ";
      // }
      // cout << endl;
      if (tokens.front().type == TokenType::INSTRUCTION_TOKEN) {
        if (tokens.front().tvalue == "ADD") {
          text_code.push_back('\x03');
          text_code.push_back('\x05');
          location = getAddrValueFromOperand(operands.back(), line);
          getBytes(bigToLittle(location), bytes);
          for (int indx = 0; indx < 4; ++indx){
            text_code.push_back(bytes[indx]);
          }

        } else if (tokens.front().tvalue == "SUB") {
          text_code.push_back('\x2b');
          text_code.push_back('\x05');
          location = getAddrValueFromOperand(operands.back(), line);
          getBytes(bigToLittle(location), bytes);
          for (int indx = 0; indx < 4; ++indx){
            text_code.push_back(bytes[indx]);
          }

        } else if (tokens.front().tvalue == "MOV") {
          // MOV THAT THE REGISTER IS THE DESTINATION
          if (operands.front().front().tvalue == "EAX") {
            if (operands.back().front().tvalue == "1") {
              // mov eax, 0
              text_code.push_back('\xb8');
              text_code.push_back('\x01');
              text_code.push_back('\x00');
              text_code.push_back('\x00');
              text_code.push_back('\x00');
              text_code.push_back('\x90');

            } else {
              text_code.push_back('\xa1');
              location = getAddrValueFromOperand(operands.back(), line);
              getBytes(bigToLittle(location), bytes);
              for (int indx = 0; indx < 4; ++indx){
                text_code.push_back(bytes[indx]);
              }
              text_code.push_back('\x90');
            }
          } else if (operands.front().front().tvalue == "EBX") {
            if (operands.back().front().tvalue == "0") {
              // mov eax, 0
              text_code.push_back('\xbb');
              text_code.push_back('\x00');
              text_code.push_back('\x00');
              text_code.push_back('\x00');
              text_code.push_back('\x00');
              text_code.push_back('\x90');

            } else {
              text_code.push_back('\x8b');
              text_code.push_back('\x1d');
              location = getAddrValueFromOperand(operands.back(), line);
              getBytes(bigToLittle(location), bytes);
              for (int indx = 0; indx < 4; ++indx){
                text_code.push_back(bytes[indx]);
              }

            }

          } else if (operands.front().front().tvalue == "EDX") {
            text_code.push_back('\x8b');
            text_code.push_back('\x15');
            location = getAddrValueFromOperand(operands.back(), line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }

          // MOV THAT THE MEMORY IS THE DESTINATION (REG IN THE LAST OP)
          } else if (operands.back().front().tvalue == "EAX") {
            text_code.push_back('\xa3');
            location = getAddrValueFromOperand(operands.front(), line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "EDX") {
            text_code.push_back('\x89');
            text_code.push_back('\x15');
            location = getAddrValueFromOperand(operands.front(), line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }

          }
        } else if (tokens.front().tvalue == "IMUL") {
            // imul eax, ebx
            text_code.push_back('\x0f');
            text_code.push_back('\xaf');
            text_code.push_back('\xc3');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');

        } else if (tokens.front().tvalue == "CDQ") {
            // cltd
            text_code.push_back('\x99');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');

        } else if (tokens.front().tvalue == "IDIV") {
            // idiv eax, ebx
            text_code.push_back('\xf7');
            text_code.push_back('\xfb');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');

        } else if (tokens.front().tvalue == "CMP") {
            // cmp eax, 0
            text_code.push_back('\x83');
            text_code.push_back('\xf8');
            text_code.push_back('\x00');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');

        } else if (tokens.front().tvalue == "JMP") {
            text_code.push_back('\xe9');
            location = calculateJump(operands.front(), program_counter, line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

        } else if (tokens.front().tvalue == "JL") {
            text_code.push_back('\x0f');
            text_code.push_back('\x8c');
            location = calculateJump(operands.front(), program_counter, line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }

        } else if (tokens.front().tvalue == "JG") {
            text_code.push_back('\x0f');
            text_code.push_back('\x8f');
            location = calculateJump(operands.front(), program_counter, line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }

        } else if (tokens.front().tvalue == "JE") {
            text_code.push_back('\x0f');
            text_code.push_back('\x84');
            location = calculateJump(operands.front(), program_counter, line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }

        } else if (tokens.front().tvalue == "PUSH") {
          if (operands.front().front().tvalue == "EAX") {
            text_code.push_back('\x50');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');

          } else if (operands.front().front().tvalue == "DWORD") {
            if (operands.back().front().type == TokenType::SYMBOL) {
              text_code.push_back('\x68');
              tokens_no_dword.assign(operands.back().begin() + 1, operands.back().end());
              location = getAddrValueFromOperand(tokens_no_dword, line);
              getBytes(bigToLittle(location), bytes);
              for (int indx = 0; indx < 4; ++indx){
                text_code.push_back(bytes[indx]);
              }
              text_code.push_back('\x90');
            } else {
              text_code.push_back('\x6a');
              int value;

              if (operands.back().front().type == TokenType::NUMBER_HEX) {
                value = std::stoi(operands.back().front().tvalue, nullptr, 16);
              } else if (operands.back().front().type == TokenType::NUMBER_DECIMAL) {
                value = std::stoi(operands.back().front().tvalue);
              }
              getBytes(bigToLittle(value), bytes);
              for (int indx = 0; indx < 4; ++indx){
                text_code.push_back(bytes[indx]);
              }
              text_code.push_back('\x90');

            }
          }
        } else if (tokens.front().tvalue == "POP") {
          if (operands.front().front().tvalue == "EAX") {
            text_code.push_back('\x58');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');

          } else if (operands.front().front().tvalue == "EDX") {
            text_code.push_back('\x5a');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
          }

        } else if (tokens.front().tvalue == "INT") {
            // int 80h
            text_code.push_back('\xcd');
            text_code.push_back('\x80');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');
            text_code.push_back('\x90');

        } else if (tokens.front().tvalue == "CALL") {
          if (operands.back().front().tvalue == "READCHAR") {
            text_code.push_back('\xe8');
            location = calculateJump(operands.front(), program_counter, line);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "WRITECHAR") {
            text_code.push_back('\xe8');
            location = calculateCall(operands.front(), program_counter, line, offset_WriteChar);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "READINTEGERADDR") {
            text_code.push_back('\xe8');
            location = calculateCall(operands.front(), program_counter, line, offset_ReadInt);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "WRITEINTEGERADDR") {
            text_code.push_back('\xe8');
            location = calculateCall(operands.front(), program_counter, line, offset_WriteInt);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "READHEXA") {
            text_code.push_back('\xe8');
            location = calculateCall(operands.front(), program_counter, line, offset_ReadHex);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "WRITEHEXA") {
            text_code.push_back('\xe8');
            location = calculateCall(operands.front(), program_counter, line, offset_WriteHex);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "READSTRING") {
            text_code.push_back('\xe8');
            location = calculateCall(operands.front(), program_counter, line, offset_ReadString);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          } else if (operands.back().front().tvalue == "WRITESTRING") {
            text_code.push_back('\xe8');
            location = calculateCall(operands.front(), program_counter, line, offset_WriteString);
            getBytes(bigToLittle(location), bytes);
            for (int indx = 0; indx < 4; ++indx){
              text_code.push_back(bytes[indx]);
            }
            text_code.push_back('\x90');

          }
        } // CLOSE CASES
      } // Instruction CLOSE
    } else if (data_section) {
      int num = 0;
      operands = parser.groupOps(program.tokens.at(line));
      program_counter += (operands.size() * 4);
      for (const auto op : operands) {
        if (op.front().type == TokenType::NUMBER_HEX) {
          num = std::stoi(op.front().tvalue, nullptr, 16);
        } else if (op.front().type == TokenType::NUMBER_DECIMAL) {
          num = std::stoi(op.front().tvalue);
        }
        getBytes(bigToLittle(num), bytes);
        for (int indx = 0; indx < 4; ++indx){
          data_code.push_back(bytes[indx]);
        }

      }

    } else {
      if (program.tokens.at(line).front().tvalue == "SECTION" &&
          program.tokens.at(line).back().tvalue == ".DATA") {
        data_section = true;
      }
    }

  }
  appendIOCode();
  showTextCode();
  showDataCode();
  createExec();
}

void SecondPass::writeObjectFile() {
  std::ofstream object_file;
  object_file.open(program.file.name() + ".obj");
  for (auto code : exec_code) {
    object_file << code << " ";
  }
  object_file.close();
}

void SecondPass::showObjectCode() {
    for (auto code : exec_code) {
      cout << code << " ";
    }
    cout << endl;
}

void SecondPass::showTextCode() {
  cout << "TEXT SECTION " << endl;
    for (int indx = 0; indx < text_code.size(); ++indx) {
      if (indx % 6 == 0) {
        cout << endl;
      }
      cout << hex(text_code.at(indx)) << " ";
    }
    cout << endl;
}

void SecondPass::showDataCode() {
  cout << "DATA SECTION " << endl;
    for (int indx = 0; indx < data_code.size(); ++indx) {
      if (indx % 4 == 0) {
        cout << endl;
      }
      cout << hex(data_code.at(indx)) << " ";
    }
    cout << endl;
}

int SecondPass::getAddrValueFromOperand(vector <Token> operand, int line) {
  try {
    vector<Token> operands_no_bracket;
    for (const auto tk : operand) {
      if ((tk.type != TokenType::OPEN_BRACKET) &&
          (tk.type != TokenType::CLOSE_BRACKET)) {
        operands_no_bracket.push_back(tk);
      }
    }
    int addr = symbol_table.getSymbolAddress(operands_no_bracket.at(0));
    int addition = 0;
    if (operands_no_bracket.size() > 1) {
      if (operands_no_bracket.back().type == TokenType::NUMBER_HEX) {
        addition = std::stoi(operands_no_bracket.back().tvalue, nullptr, 16);
      } else if (operand.back().type == TokenType::NUMBER_DECIMAL) {
        addition = std::stoi(operands_no_bracket.back().tvalue);
      } else {
        addition = std::stoi(operands_no_bracket.back().tvalue);
      }
    }
    return addr + addition;
  } catch(const std::out_of_range &e) {
    cout << "[SEMANTIC ERR | Line " << line + 1 << "] Operand " << operand.at(0).tvalue << " not found in the Symbols Table." << endl;
    return -1;
  } catch(const std::invalid_argument &e) {
    cout << "[ERR | Line " << line + 1 << "] Could not convert " << operand.back().tvalue << endl;
    return -1;
  }
}
void SecondPass::getBytes(int num, char bytes[]) {
  int num_byte;
  bytes[3] = num & 0x000000ff;
  bytes[2] = (num & 0x0000ff00) >> 8;
  bytes[1] = (num & 0x00ff0000) >> 16;
  bytes[0] =  num >> 24;
}

int SecondPass::bigToLittle(int num) {
  int swapped;
  swapped = 	((num>>24)&0xff) | // move byte 3 to byte 0
                ((num<<8)&0xff0000) | // move byte 1 to byte 2
                ((num>>8)&0xff00) | // move byte 2 to byte 1
                ((num<<24)&0xff000000); // byte 0 to byte 3
  return swapped;
}

string SecondPass::stringfyOps(vector <Token> op) {
  string operand = "";
  if (op.size() > 0) {
    for (const auto tk : op) {
      operand = operand + tk.tvalue + " ";
    }
    operand.pop_back();
  }
  return operand;
}

int SecondPass::calculateJump(vector <Token> operand, int pc, int line) {
  int location = getAddrValueFromOperand(operand, line);
  // cout << "JUMP l:" << location << "  pc: " << pc;
  // cout << " r: " << (location - pc) <<  endl;
  return location - pc;
}

int SecondPass::calculateCall(vector <Token> operand, int pc, int line, int offset) {
  int base_addr = symbol_table.getSymbolAddress("READCHAR");
  // cout << "JUMP l:" << base_addr << "  pc: " << pc;
  // cout << " r: " << offset <<  endl;
  return (base_addr + offset + 1) - pc;
}

void SecondPass::appendIOCode() {
  std::ifstream ifs("io_code/IOFunc.objdump");

  if (!ifs.is_open()) {
    cout << "[ERR] Could not open IOFunc code!" << endl;
    exit(-1);
  }

  string line;
  char aux_byte[3000];
  int i = 0;
  int j = 0;

  while( std::getline(ifs, line) ) {
    for ( i = 6; i < 41; i++ ) { //14, 23, 32
      if ( i == 14 || i == 23 || i == 32) i++;
      aux_byte[j] = (char) ( (convertChar( (char) line[i]) * 16 ) +
        ( convertChar( (char) line[++i] ) ));
      j++;
    }
  }

  for (int indx = 0; indx < j; ++indx) {
    text_code.push_back(aux_byte[indx]);
  }
}

void SecondPass::createExec() {
  elfio writer;

  writer.create( ELFCLASS32, ELFDATA2LSB );

  writer.set_os_abi( ELFOSABI_LINUX );
  writer.set_type( ET_EXEC );
  writer.set_machine( EM_386 );

  section* text_sec = writer.sections.add( ".text" );
  text_sec->set_type( SHT_PROGBITS );
  text_sec->set_flags( SHF_ALLOC | SHF_EXECINSTR );
  text_sec->set_addr_align( 0x10 );

  char text[0x100000];
  for (int indx = 0; indx < text_code.size(); ++indx) {
    text[indx] = text_code.at(indx);
  }

  text_sec->set_data( text, text_code.size() );
  segment* text_seg = writer.segments.add();
  text_seg->set_type( PT_LOAD );
  text_seg->set_virtual_address( 0x08048000 );
  text_seg->set_physical_address( 0x08048000 );
  text_seg->set_flags( PF_X| PF_R );
  text_seg->set_align( 0x1000 );

  text_seg->add_section_index( text_sec->get_index(),
                               text_sec->get_addr_align() );

  section* data_sec = writer.sections.add( ".data" );
  data_sec->set_type( SHT_PROGBITS );
  data_sec->set_flags( SHF_ALLOC | SHF_WRITE );
  data_sec->set_addr_align( 0x4 );

  char data[0x100000];
  for (int indx = 0; indx < data_code.size(); ++indx) {
    data[indx] = data_code.at(indx);
  }
  data_sec->set_data( data, data_code.size() );

  segment* data_seg = writer.segments.add();
  data_seg->set_type( PT_LOAD );
  data_seg->set_virtual_address( begin_data );
  data_seg->set_physical_address( begin_data );
  data_seg->set_flags( PF_W | PF_R );
  data_seg->set_align( 0x1000 );
  data_seg->add_section_index( data_sec->get_index(),
                               data_sec->get_addr_align() );

  writer.set_entry( 0x08048000 );
  writer.save( program.file.name() + ".e" );
}
