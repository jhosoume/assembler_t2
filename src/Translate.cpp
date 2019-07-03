#include "Translate.hpp"

Translate::Translate(const Parser &parser,
                     const Program &prog
                    )
  : parser{parser}, program{prog}
  {}

void Translate::exec() {
  vector<Token> tokens;
  vector < vector<Token> > operands;
  string aux_string = "";
  nasm_code.push_back("global _start\n");
  for (unsigned int line = 0; line < program.tokens.size(); ++line) {
    // cout << line << " | ";
    tokens = program.tokens.at(line);

    // ADDING LABEL
    if (parser.hasLabel(tokens)) {
      // If has label, put iterator after label
      nasm_code.push_back(tokens.front().tvalue + ":\n");
      tokens.assign(tokens.begin() + 2, tokens.end());
      // Add label
    }
    // Geting operands
    operands = parser.groupOps(program.tokens.at(line));
    // cout << "OPERANDS: ";
    // for (auto op : operands) {
    //   cout << stringfyOps(op);
    //   cout <<  " | ";
    // }
    // cout << endl;

    // DEALING WITH SECTION
    if (tokens.front().type == TokenType::SECTION) {
      if (tokens.back().type == TokenType::DATA_SECTION) {
        addInputOutput();
        nasm_code.push_back("section .data\n");
      } else if (tokens.back().type == TokenType::TEXT_SECTION) {
        nasm_code.push_back("section .text\n");
        nasm_code.push_back("_start: \n");
      }

      // DEALING WITH ADD
    } else if (tokens.front().tvalue == "ADD") {
      aux_string = "add eax, [" + stringfyOps(operands.front(), false) + "]\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH SUB
    } else if (tokens.front().tvalue == "SUB") {
      aux_string = "sub eax, [" + stringfyOps(operands.front(), false) + "]\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH MULT
    } else if (tokens.front().tvalue == "MULT") {
      aux_string = "mov ebx, [" + stringfyOps(operands.front(), false) + "]\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("imul eax, ebx\n");

      // DEALING WITH DIV
    } else if (tokens.front().tvalue == "DIV") {
      aux_string = "mov ebx, [" + stringfyOps(operands.front(), false) + "]\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("cdq\n");
      nasm_code.push_back("idiv ebx\n");

      // DEALING WITH JMP
    } else if (tokens.front().tvalue == "JMP") {
      aux_string = "jmp " + stringfyOps(operands.front(), true) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH JMPN
    } else if (tokens.front().tvalue == "JMPN") {
      nasm_code.push_back("cmp eax, 0\n");
      aux_string = "jl " + stringfyOps(operands.front(), true) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH JMPP
    } else if (tokens.front().tvalue == "JMPP") {
      nasm_code.push_back("cmp eax, 0\n");
      aux_string = "jg " + stringfyOps(operands.front(), true) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH JMPZ
    } else if (tokens.front().tvalue == "JMPZ") {
      nasm_code.push_back("cmp eax, 0\n");
      aux_string = "je " + stringfyOps(operands.front(), true) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH COPY
    } else if (tokens.front().tvalue == "COPY") {
      aux_string = "mov edx, [" + stringfyOps(operands.front(), false) + "]\n";
      nasm_code.push_back(aux_string);
      aux_string = "mov [" + stringfyOps(operands.back(), false) + "], edx\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH INPUT
    } else if (tokens.front().tvalue == "INPUT") {
      nasm_code.push_back("push eax\n");
      aux_string = "push DWORD ";
      aux_string = aux_string + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call ReadIntegerAddr\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop eax\n");

      // DEALING WITH OUTPUT
    } else if (tokens.front().tvalue == "OUTPUT") {
      nasm_code.push_back("push eax\n");
      aux_string = "push DWORD ";
      aux_string = aux_string + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call WriteIntegerAddr\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop eax\n");

      // DEALING WITH LOAD
    } else if (tokens.front().tvalue == "LOAD") {
      aux_string = "mov eax, [" + stringfyOps(operands.front(), false) + "]\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH STORE
    } else if (tokens.front().tvalue == "STORE") {
      aux_string = "mov [" + stringfyOps(operands.front(), false) + "], eax\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH STOP
    } else if (tokens.front().tvalue == "STOP") {
      nasm_code.push_back("mov eax, 1\n");
      nasm_code.push_back("mov ebx, 0\n");
      nasm_code.push_back("int 80h\n");

      // DEALING WITH INPUT CHAR
    } else if (tokens.front().tvalue == "C_INPUT") {
      nasm_code.push_back("push eax\n");
      aux_string = "push DWORD ";
      aux_string = aux_string + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call ReadChar\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop eax\n");

      // DEALING WITH OUTPUT CHAR
    } else if (tokens.front().tvalue == "C_OUTPUT") {
      aux_string = "push DWORD " + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call WriteChar\n");
      nasm_code.push_back("pop edx\n");

      // TODO DEALING WITH INPUT STRING
    } else if (tokens.front().tvalue == "S_INPUT") {
      nasm_code.push_back("push eax\n");
      aux_string = "push DWORD " + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      aux_string = "push DWORD " + stringfyOps(operands.back(), true) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call ReadString\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop eax\n");

      // DEALING WITH OUTPUT STRING
    } else if (tokens.front().tvalue == "S_OUTPUT") {
      nasm_code.push_back("push eax\n");
      aux_string = "push DWORD " + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      aux_string = "push DWORD " + stringfyOps(operands.back(), true) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call WriteString\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop eax\n");

      // DEALING WITH INPUT HEX
    } else if (tokens.front().tvalue == "H_INPUT") {
      nasm_code.push_back("push eax\n");
      aux_string = "push DWORD ";
      aux_string = aux_string + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call ReadHexa\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop eax\n");

      // DEALING WITH OUTPUT HEX
    } else if (tokens.front().tvalue == "H_OUTPUT") {
      nasm_code.push_back("push eax\n");
      aux_string = "push DWORD ";
      aux_string = aux_string + stringfyOps(operands.front(), false) + "\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call WriteHexa\n");
      nasm_code.push_back("pop edx\n");
      nasm_code.push_back("pop eax\n");
      // DEALING WITH CONST
    } else if (tokens.front().tvalue == "CONST") {
      aux_string = "DD " + stringfyOps(operands.back(), true) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH SPACE
    } else if (tokens.front().tvalue == "SPACE") {
      if (operands.size() > 0) {
        aux_string = "DD ";
        for (int indx = 0; indx < std::stoi(operands.back().back().tvalue); ++indx) {
          aux_string = aux_string + "0, ";
        }
        aux_string.pop_back();
        aux_string.pop_back();
        aux_string = aux_string + "\n";
        nasm_code.push_back(aux_string);
      } else {
        aux_string = "DD 0\n";
        nasm_code.push_back(aux_string);
     }

      //FINISH
    }

    // for (const auto token : tokens) {
    //   cout << token.tvalue << " ";
    // }
    // cout << endl;
  }
  // showNasmCode();
}

void Translate::writeNasmFile() {
  std::ofstream nasm_file;
  nasm_file.open(program.file.name() + ".s");
  for (auto code : nasm_code) {
    nasm_file << code << " ";
  }
  nasm_file.close();
}

void Translate::showNasmCode() {
  cout << endl << "***********" << endl;
  cout << "NASM Code" << endl << endl;
    for (auto code : nasm_code) {
      cout << code;
    }
  cout << "***********" << endl;
    cout << endl;
}

string Translate::stringfyOps(vector <Token> op, bool std_size) {
  string operand = "";
  string value = "";
  int acc = 0;
  if (op.size() > 0) {
    for (const auto tk : op) {
      if (std_size) {
        value = tk.tvalue;
      } else {
        if (tk.type == TokenType::NUMBER_DECIMAL) {
          acc = std::stoi(tk.tvalue);
          acc = acc * 4;
          value = std::to_string(acc);
        } else if (tk.type == TokenType::NUMBER_HEX) {
          acc = std::stoi(tk.tvalue, nullptr, 16);
          acc = acc * 4;
          value = std::to_string(acc);
        } else {
          value = tk.tvalue;
        }
      }
      operand = operand + value + " ";
    }
    operand.pop_back();
  }
  return operand;
}

void Translate::addInputOutput() {
  vector <string> fileNames = {"IA32_IO/ReadChar.s",
                               "IA32_IO/WriteChar.s",
                               "IA32_IO/ReadIntegerAddr.s",
                               "IA32_IO/WriteIntegerAddr.s",
                               "IA32_IO/ReadHexa.s",
                               "IA32_IO/WriteHexa.s",
                               "IA32_IO/ReadString.s",
                               "IA32_IO/WriteString.s",
                             };
  string line;
  for (const auto name : fileNames) {
    std::ifstream ifs(name);
    // Testing if file can be oppened
    if (!ifs.is_open()) {
      throw std::runtime_error("[ERR] " + name + " could not open IA32 input output files!\n This binary should have an IA 32 directory in the src foulder with the asm files for INPUT and OUTPUT");
    }
    nasm_code.push_back("\n");
    while(std::getline(ifs, line)) {
      nasm_code.push_back(line + "\n");
    }
    nasm_code.push_back("\n");
  }
}
