#include <stdio.h>
#include <stdlib.h>

int main()
{
  /* Insert your four bytes of ASCII for your secret message */
  /* The 0x prefix above indicates a hexadecimal number */
  setbuf(stdout, NULL);
  int z = 0x54494D45;
  char* c = (char*)&z;
  printf("%c", *c++);
  printf("%c", *c++);
  printf("%c", *c++);
  printf("%c\n", *c);

  FILE *fp = fopen("lab02-data.little.dat", "r");
  if (fp == NULL) {
    printf("Error opening file");
  }
  fseek(fp, 0L, SEEK_END);
  int sz = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  printf("Size  = %d bytes\n", sz);

  long *data = malloc(sz);
  fread(data, sizeof(long), sz/sizeof(long), fp);

  //int* data = malloc(sz);
  //fread(data, sizeof(int), sz/sizeof(int), fp);
  
  for (int i = 0; i < sz/sizeof(long) ; i++){
    //printf("Data Point %d: %3d \n", i, data[i]);
    printf("Data Point %d: %20ld \n", i, data[i]);
  }
}

