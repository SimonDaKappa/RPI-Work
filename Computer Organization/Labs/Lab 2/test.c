#include <stdio.h>
#include <stdlib.h>

int main(){
  int z = 0x54494D45;
  char* c = (char*)&z;
  printf("%c\n", *c++);
  printf("%c\n", *c++);
  printf("%c\n", *c++);
  printf("%c\n", *c);
  return 0;
}