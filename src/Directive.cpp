#include "Directive.hpp"

Directive::Directive(string name, int max_operands, int size)
  : name{name}, max_operands{max_operands}, size{size}
  {}
