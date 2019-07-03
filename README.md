# assembler_t2

MATÉRIA: Software Básico
SEMESTRE: Primeiro Semestre de 2019

Juliana Mayumi Hosoume 18/0048864
Luisa Sinzker Fantin   14/0151893

Compilado com g++ versão:
gcc version 5.5.0 20171010 (Ubuntu 5.5.0-12ubuntu1~16.04)


Para compilar o código, na pasta principal (root) do projeto:
>>> ./make

Para compilar do zero:
>>> ./make clean
>>> ./make

Para executar o programa:
>>> ./bin/tradutor arquivo.asm
[arquivo.asm pode ser substituido por qualquer nome de arquivo]


Para utilizar para arquivos em outra pasta, fazer como
>>> ./bin/tradutor testes/bin.asm

Serão geradas duas saídas no diretório do arquivo de entrada, uma arquivo com extensão .pre com o pré-processamento e outro arquivo com extensão .s, com a tradução de assembly inventado para assembly IA-32 do padrão NASM.

Diretórios:
bin : arquivo executável do tradutor
build : arquivos objeto
include : headers dos arquivos C++
src : código em C++ do tradutor
tests : alguns testes utilziados
Makefile : arquivo que auxilia na compilação

Para compilar sem utilizar o Make, realizar:

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/helper.o src/helper.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/SymbolTable.o src/SymbolTable.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Parser.o src/Parser.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/SecondPass.o src/SecondPass.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/tradutor.o src/tradutor.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Scanner.o src/Scanner.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Instruction.o src/Instruction.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Translate.o src/Translate.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/SymbolData.o src/SymbolData.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/InstructionTable.o src/InstructionTable.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/MacroTable.o src/MacroTable.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Macro.o src/Macro.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Directive.o src/Directive.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/LineCounter.o src/LineCounter.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/EquTable.o src/EquTable.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/PreProcessing.o src/PreProcessing.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/DirectiveTable.o src/DirectiveTable.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Program.o src/Program.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/Token.o src/Token.cpp

 g++ -std=c++11 --pedantic -O3 -I include -c -o build/FirstPass.o src/FirstPass.cpp

 g++ build/helper.o build/SymbolTable.o build/Parser.o build/SecondPass.o build/tradutor.o build/Scanner.o build/Instruction.o build/Translate.o build/SymbolData.o build/InstructionTable.o build/MacroTable.o build/Macro.o build/Directive.o build/LineCounter.o build/EquTable.o build/PreProcessing.o build/DirectiveTable.o build/Program.o build/Token.o build/FirstPass.o -o bin/tradutor -lm
