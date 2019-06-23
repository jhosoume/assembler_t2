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
    cout << line << " | ";
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
      nasm_code.push_back("section ");
      if (tokens.back().type == TokenType::DATA_SECTION) {
        nasm_code.back() = nasm_code.back() + ".data\n";
      } else if (tokens.back().type == TokenType::TEXT_SECTION) {
        nasm_code.back() = nasm_code.back() + ".text\n";
        nasm_code.push_back("_start: \n");
      }

      // DEALING WITH ADD
    } else if (tokens.front().tvalue == "ADD") {
      aux_string = "add eax, [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH SUB
    } else if (tokens.front().tvalue == "SUB") {
      aux_string = "sub eax, [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH MULT
    } else if (tokens.front().tvalue == "MULT") {
      aux_string = "mov ebx, [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("imul eax, ebx\n");

      // DEALING WITH DIV
    } else if (tokens.front().tvalue == "DIV") {
      aux_string = "mov ebx, [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("cdq\n");
      nasm_code.push_back("idiv ebx\n");

      // DEALING WITH JMP
    } else if (tokens.front().tvalue == "JMP") {
      aux_string = "jmp " + stringfyOps(operands.front()) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH JMPN
    } else if (tokens.front().tvalue == "JMPN") {
      nasm_code.push_back("cmp eax, 0\n");
      aux_string = "jl " + stringfyOps(operands.front()) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH JMPP
    } else if (tokens.front().tvalue == "JMPP") {
      nasm_code.push_back("cmp eax, 0\n");
      aux_string = "jg " + stringfyOps(operands.front()) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH JMPZ
    } else if (tokens.front().tvalue == "JMPZ") {
      nasm_code.push_back("cmp eax, 0\n");
      aux_string = "je " + stringfyOps(operands.front()) + "\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH COPY
    } else if (tokens.front().tvalue == "COPY") {
      aux_string = "mov edx, [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);
      aux_string = "mov [" + stringfyOps(operands.back()) + "], edx\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH INPUT
    } else if (tokens.front().tvalue == "INPUT") {
      nasm_code.push_back("push eax\n");
      nasm_code.push_back("call WriteInteger\n");
      aux_string = "mov [";
      aux_string = aux_string + stringfyOps(operands.front()) + "], eax\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("pop eax\n");

      // DEALING WITH OUTPUT
    } else if (tokens.front().tvalue == "OUTPUT") {
      aux_string = "push DWORD [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);
      nasm_code.push_back("call WriteInteger\n");
      aux_string = "pop DWORD [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH LOAD
    } else if (tokens.front().tvalue == "LOAD") {
      aux_string = "mov eax, [" + stringfyOps(operands.front()) + "]\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH STORE
    } else if (tokens.front().tvalue == "STORE") {
      aux_string = "mov [" + stringfyOps(operands.front()) + "], eax\n";
      nasm_code.push_back(aux_string);

      // DEALING WITH STOP
    } else if (tokens.front().tvalue == "STORE") {
      nasm_code.push_back("mov eax, 1\n");
      nasm_code.push_back("mov ebx, 0\n");
      nasm_code.push_back("int 80h\n");

    }




    for (const auto token : tokens) {
      cout << token.tvalue << " ";
    }
    cout << endl;
  }
  showNasmCode();
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

string Translate::stringfyOps(vector <Token> op) {
  string operand = "";
  if (op.size() > 0) {
    for (const auto tk : op) {
      operand = operand + tk.tvalue + " ";
    }
    operand.pop_back();
  }
  return operand;
}
