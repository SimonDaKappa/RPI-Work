/* 
Lab 6: Decoding the Mysteries of MIPS
CSCI-2500 Spring 2023
Prof. Slota 
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// define BIT type as a char (i.e., one byte)
typedef char BIT;
#define TRUE 1
#define FALSE 0
#define UNDEF -1

/******************************************************************************/
/* Normal circuits */
/* Modify/add additional circuits as necessary (e.g., 3-input AND gate) */
/******************************************************************************/
BIT not_gate(BIT A)
{
  return (!A);
}

BIT or_gate(BIT A, BIT B)
{
  return (A || B);
}

BIT and_gate(BIT A, BIT B)
{
  return (A && B);
}

BIT and_gate3(BIT A, BIT B, BIT C)
{
  return and_gate(A, and_gate(B, C));
}

BIT xor_gate(BIT A, BIT B)
{
  BIT nA = not_gate(A);
  BIT nB = not_gate(B);
  BIT x0 = and_gate(A, nB);
  BIT x1 = and_gate(nA, B);
  return or_gate(x0, x1);
}

void decoder2(BIT* I, BIT EN, BIT* O)
{
  BIT nI1 = not_gate(I[1]);
  BIT nI0 = not_gate(I[0]);
  O[0] = and_gate(nI1, nI0);
  O[1] = and_gate(nI1, I[0]);
  O[2] = and_gate(I[1], nI0);
  O[3] = and_gate(I[1],  I[0]);
  
  // Note use of EN (enable) line below
  for (int i = 0; i < 4; ++i)
    O[i] = and_gate(EN, O[i]);
  
  return;
}



/******************************************************************************/
/* Checkpoint 1 functions */
/* Add helper functions as necessary. I did:
  - One for converting integer->2's complement binary
  - One for converting register string to binary representation */
/******************************************************************************/
void convert_to_binary_char(int a, char* A, int length)
{
  if (a >= 0) {
    for (int i = 0; i < length; ++i) {
      A[i] = (a % 2 == 1 ? '1' : '0');
      a /= 2;
    }
  } else {
    a += 1;
    for (int i = 0; i < length; ++i) {
      A[i] = (a % 2 == 0 ? '1' : '0');
      a /= 2;
    }
  }
}

void set_register(char* input, char* output)
{
  if (strcmp(input, "t0") == 0)
    strncpy(output, "00010", 5);
  else if (strcmp(input, "s0") == 0)
    strncpy(output, "00001", 5);
}

int convert_instructions()
{
  char line[256] = {0};
  int counter = 0;
  while (fgets(line, 256, stdin) != NULL) {
    BIT output[32] = {FALSE};
    char inst[256] = {0};
    char op1[256] = {0};
    char op2[256] = {0};
    char op3[256] = {0};
    sscanf(line, "%s %s %s %s", inst, op1, op2, op3);
    
    char temp_output[33] = {0};
    char rs[6] = {0};
    char rt[6] = {0};
    char rd[6] = {0};
    char imm[17] = {0};
    char address[27] = {0};
    
    if (strcmp(inst, "lw") == 0) {
      convert_to_binary_char(atoi(op3), imm, 16);
      set_register(op1, rt);
      set_register(op2, rs);
      strncpy(&temp_output[0], imm, 16);
      strncpy(&temp_output[16], rt, 5);
      strncpy(&temp_output[21], rs, 5);
      strncpy(&temp_output[26], "110001", 6);      
    } else if (strcmp(inst, "add") == 0) {
      set_register(op1, rd);
      set_register(op2, rs);
      set_register(op3, rt);
      strncpy(&temp_output[0], "000001", 6);
      strncpy(&temp_output[6], "00000", 5);
      strncpy(&temp_output[11], rd, 5);
      strncpy(&temp_output[16], rt, 5);
      strncpy(&temp_output[21], rs, 5);
      strncpy(&temp_output[26], "000000", 6);      
    } else if (strcmp(inst, "j") == 0) {
      convert_to_binary_char(atoi(op1), address, 26);
      strncpy(&temp_output[0], address, 26);
      strncpy(&temp_output[26], "010000", 6);      
    }
    
    for (int i = 0; i < 32; ++i)
      output[i] = (temp_output[i] == '1' ? TRUE : FALSE); 
    
    for (int i = 31; i >= 0; --i) {
      printf("%d", output[i]);
    }
    printf("\n");
    ++counter;
  }
  
  return counter;
}

/******************************************************************************/
/* Checkpoint 2 circuits */
/******************************************************************************/
void decoder3(BIT* I, BIT EN, BIT* O)
{
  O[0] = and_gate3(not_gate(I[2]), not_gate(I[1]), not_gate(I[0]));
  O[1] = and_gate3(not_gate(I[2]), not_gate(I[1]), I[0]);
  O[2] = and_gate3(not_gate(I[2]), I[1], not_gate(I[0]));
  O[3] = and_gate3(not_gate(I[2]), I[1], I[0]);
  O[4] = and_gate3(I[2], not_gate(I[1]), not_gate(I[0]));
  O[5] = and_gate3(I[2], not_gate(I[1]), I[0]);
  O[6] = and_gate3(I[2], I[1], not_gate(I[0]));
  O[7] = and_gate3(I[2], I[1], I[0]);
  
  for (int i = 0; i < 8; ++i)
    O[i] = and_gate(EN, O[i]);
  
  return;
}

void decoder5(BIT* I, BIT EN, BIT* O)
{
   BIT EN_O[4] = {FALSE};
   decoder2(&I[3], EN, EN_O);
   decoder3(I, EN_O[3], &O[24]);
   decoder3(I, EN_O[2], &O[16]);
   decoder3(I, EN_O[1], &O[8]);
   decoder3(I, EN_O[0], &O[0]);
   
  for (int i = 0; i < 32; ++i)
    O[i] = and_gate(EN, O[i]);
  
}


/******************************************************************************/
/* Insane in the membmain */
/******************************************************************************/
int main()
{
  // convert some arbitrary number of instructions from stdin
  convert_instructions();
  
  // Unit test for 5-to-32 decoder
  printf("\n===== Unit test for 5-to-32 decoder =====\n");
  printf("decoder( I4, I3, I2, I1, I0 ) | ( O31, O30, ..., O1, O0 )\n");
  printf("------------------------------|--------------------------------------------------------------------------------------------------\n" );
  BIT I[5] = {0};
  BIT O[32] = {0};
  for (I[4] = 0; I[4] < 2; ++I[4])
    for (I[3] = 0; I[3] < 2; ++I[3])
      for (I[2] = 0; I[2] < 2; ++I[2])
        for (I[1] = 0; I[1] < 2; ++I[1])
          for (I[0] = 0; I[0] < 2; ++I[0]) {
              decoder5(I, TRUE, O);
              printf( "decoder( %2d, %2d, %2d, %2d, %2d, ) | ( ",
                I[4], I[3], I[2], I[1], I[0]);
              printf("%2d", O[31]);
              for (int i = 30; i >= 0; --i)
                printf(", %2d", O[i]);
              printf(" )\n");
            }

  return 0;
}

