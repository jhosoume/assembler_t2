FIVE_: EQU 5
SECTION TEXT

INPUT INIT
INPUT POSITIVE
INPUT NEGATIVE
INPUT NEUTRAL
INPUT VECTOR
INPUT VECTOR + 1
INPUT VECTOR + 2

OUTPUT NEUTRAL
JMP INITIAL_LABEL

MA_LABEL:
OUTPUT NEGATIVE
LOAD NEGATIVE
MULT TEN
DIV FIVE
STORE NEGATIVE
OUTPUT NEGATIVE
COPY NEGATIVE, VECTOR + 1
JMP FINAL_LABEL
BOA_LABEL:
OUTPUT POSITIVE
LOAD POSITIVE
MULT TEN
DIV FIVE
STORE POSITIVE
OUTPUT POSITIVE
COPY POSITIVE, VECTOR + 1
JMP FINAL_LABEL
NEUTRAL_LABEL:
OUTPUT NEUTRAL
LOAD NEUTRAL
MULT TEN
DIV FIVE
STORE NEUTRAL
OUTPUT NEUTRAL
COPY NEUTRAL, VECTOR + 1
JMP FINAL_LABEL

INITIAL_LABEL:
OUTPUT INIT
LOAD INIT
JMPP BOA_LABEL
JMPN MA_LABEL
JMPZ NEUTRAL_LABEL

FINAL_LABEL:
OUTPUT VECTOR
OUTPUT VECTOR + 1
OUTPUT VECTOR + 2


STOP
SECTION DATA
INIT: SPACE
POSITIVE: SPACE
NEGATIVE: SPACE
NEUTRAL: SPACE
VECTOR: SPACE 3
TEN: CONST 10
FIVE: CONST FIVE_
C: SPACE
S: space 100
