#include "Instruction.hpp"

Instruction::Instruction(string name, int n_op, int op_code)
  : name{name}, num_operands{n_op}, op_code{op_code}
  {}
