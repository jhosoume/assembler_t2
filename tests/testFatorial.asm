SECTION TEXT
INPUT NUM
COPY ONE, RESULT
COPY ONE, I
LOOP: LOAD I
SUB NUM
JMPP FIM
LOAD RESULT
MULT I
STORE RESULT
LOAD I
ADD ONE
STORE I
JMP LOOP
FIM: OUTPUT RESULT
STOP
SECTION DATA
RESULT: SPACE
I: SPACE
NUM: SPACE 1
ONE: CONST 1
