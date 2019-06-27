#include "Instruction.hpp"

Instruction::Instruction(string name, int n_op, int size, int op_code)
  : name{name}, num_operands{n_op}, size{size} op_code{op_code}
  {}
