#include "SecondPass.hpp"

struct HexCharStruct {
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o,
                                const HexCharStruct& hs) {
  return (o << std::hex << (int)hs.c);
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
  vector < vector<Token> > operands;
  bool text_section = true;
  bool data_section = false;
  int location;
  char bytes[4];
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    // cout << line << " ";
    tokens = program.tokens.at(line);
    // Not consider labels
    if (parser.hasLabel(tokens)) {
      // If has label, put iterator after label
      tokens.assign(tokens.begin() + 2, tokens.end());
    }
    if (text_section) {
      if (program.tokens.at(line).front().tvalue == "READCHAR") {
        text_section = false;
        continue;
      }
      operands = parser.groupOps(program.tokens.at(line));
      cout << "OPERANDS: ";
      for (auto op : operands) {
        cout << stringfyOps(op);
        cout <<  " | ";
      }
      cout << endl;
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
        }
      }
    } else if (data_section) {

    }
  }
  showTextCode();
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
    for (const auto code : text_code) {
      cout << hex(code) << " ";
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

  char text[text_code.size()];
  for (int indx = 0; indx < text_code.size(); ++indx) {
    text[indx] = text_code.at(indx);
  }

  text_sec->set_data( text, sizeof( text ) );
  segment* text_seg = writer.segments.add();
  text_seg->set_type( PT_LOAD );
  text_seg->set_virtual_address( 0x08048000 );
  text_seg->set_physical_address( 0x08048000 );
  text_seg->set_flags( PF_X| PF_R );
  text_seg->set_align( 0x10000 );

  text_seg->add_section_index( text_sec->get_index(),
                               text_sec->get_addr_align() );

  section* data_sec = writer.sections.add( ".data" );
  data_sec->set_type( SHT_PROGBITS );
  data_sec->set_flags( SHF_ALLOC | SHF_WRITE );
  data_sec->set_addr_align( 0x4 );
  char data[] = { '\x48', '\x65', '\x6C', '\x6C', '\x6F',// “Hello, World!\n”
                  '\x2C', '\x20', '\x57', '\x6F', '\x72',
                  '\x6C', '\x64', '\x21', '\x0A' };
  data_sec->set_data( data, sizeof( data ) );

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
