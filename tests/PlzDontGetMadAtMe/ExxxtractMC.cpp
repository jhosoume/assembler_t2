#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int convertChar(char);

int main () {
  ifstream ifs("OurFunk.objbump");

  if (!ifs.is_open()) {
    std::cout << "Deu ruim." << std::endl;
    exit(-1);
  }

  string line;
  char aux_byte[3000];
  int i = 0;
  int j = 0;

  while(std::getline(ifs, line)) {
    for(i=6; i<41; i++) { //14, 23, 32
      if(i==14 || i==23 || i==32) i++;

      aux_byte[j] = (char)((convertChar((char)line[i])*16)+(convertChar((char)line[++i])));

      j++;
    }
  }

  ifs.close();
  return 0;
}

int convertChar(char bar) {
    if((int)bar < 58) {
      return (int)bar-48;
    } else {
      return (int)bar-87;
    }
}
