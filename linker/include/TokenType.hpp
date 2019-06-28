#ifndef TOKENTYPE
#define TOKENTYPE


enum class TokenType {
  INVALID,            // Any characther that is not considered permited by the language
  NUMBER_DECIMAL,     // Number in decimal
  NUMBER_HEX,         // Number in hex
  SYMBOL,             // Any name as variables (labels)
  LABEL_COLON,        // Colon that separates label from definition
  MACRO,              // Macro definition
  ENDMACRO,              // Macro definition
  SECTION,              // Macro definition
  DATA_SECTION,              // Macro definition
  TEXT_SECTION,              // Macro definition
  DIRECTIVE_TOKEN,
  INSTRUCTION_TOKEN,
  REGISTER_TOKEN,
  COMMENT_SEMICOLON,
  COMMA_ARG_SEPARATOR,
  MACRO_PARAMETER,
  ADD_SYMBOL,         // + sign, utilized for vectors
  OPEN_BRACKET,
  CLOSE_BRACKET,
  END_HEX,
  EMPTY               // spaces or empty lines
};

#endif
