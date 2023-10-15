/* 
HW 5: C my Circuits
CSCI-2500 Spring 2023
Prof. Slota 
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>


/******************************************************************************/
/* Some defines for our circuit representations  */
/******************************************************************************/

// define BIT type as a char (i.e., one byte)
typedef char BIT;
#define TRUE 1
#define FALSE 0
#define UNDEF -1

BIT ONE[32] = {TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};
BIT ZERO[32] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
  FALSE};


/******************************************************************************/
/* Function prototypes */
/******************************************************************************/
BIT not_gate(BIT A);
BIT or_gate(BIT A, BIT B);
BIT and_gate(BIT A, BIT B);
BIT xor_gate(BIT A, BIT B);
BIT nor_gate(BIT A, BIT B);

void copy_bits(BIT* A, BIT* B);
void print_binary(BIT* A);
void set_op(char op, BIT* OP);
void convert_to_binary(int a, BIT* A);

void decoder2(BIT I0, BIT I1, BIT* O0, BIT* O1, BIT* O2, BIT* O3);
BIT multiplexor2(BIT S, BIT I0, BIT I1);
BIT multiplexor4(BIT S0, BIT S1, BIT I0, BIT I1, BIT I2, BIT I3);

void shifter(BIT* A, BIT* R, BIT Control);
void left_shifter32(BIT* A, BIT* B, BIT* R);
void multiplier16(BIT* A, BIT* B, BIT* R);
void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum);
void ALU1(BIT A, BIT B, BIT Binvert, BIT CarryIn, BIT Less, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut, BIT* Set);
void ALU32(BIT* A, BIT* B, BIT Binvert, BIT CarryIn, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut);
void Control(BIT* A, BIT* B, BIT* OP, BIT* S);

  
/******************************************************************************/
/* Functions provided for your convenience */
/******************************************************************************/
// This will set the OP bits for Control() based on the specified operation
void set_op(char op, BIT* OP)
{
  switch (op) {
    case '&': OP[2] = FALSE; OP[1] = FALSE; OP[0] = FALSE; break;
    case '|': OP[2] = FALSE; OP[1] = FALSE; OP[0] = TRUE;  break;
    case 'n': OP[2] = FALSE; OP[1] = TRUE;  OP[0] = FALSE; break;
    case '+': OP[2] = FALSE; OP[1] = TRUE;  OP[0] = TRUE;  break;
    case '-': OP[2] = TRUE;  OP[1] = FALSE; OP[0] = FALSE; break;
    case '<': OP[2] = TRUE;  OP[1] = FALSE; OP[0] = TRUE;  break;
    case 's': OP[2] = TRUE;  OP[1] = TRUE;  OP[0] = FALSE; break;
    case '*': OP[2] = TRUE;  OP[1] = TRUE;  OP[0] = TRUE;  break;
    default: break;
  }
}

void copy_bits(BIT* A, BIT* B)
{
  for (int i = 0; i < 32; ++i)
    B[i] = A[i]; 
}

void print_binary(BIT* A)
{
  for (int i = 31; i >= 0; --i)
    printf("%d", A[i]); 
}


/******************************************************************************/
/* Functions you implemented in Lab 5 */
/******************************************************************************/
BIT not_gate(BIT A)
{
  return (!A);
}

BIT or_gate(BIT A, BIT B)
{
  // TODO: implement logical OR
  return (A || B);
}

BIT and_gate(BIT A, BIT B)
{
  // TODO: implement logical AND
  return (A && B);
}

// AND/OR Simplifications

BIT or3_gate(BIT A, BIT B, BIT C) // 3-input OR gate
{
  return or_gate(or_gate(A, B), C);
}

BIT or4_gate(BIT A, BIT B, BIT C, BIT D) // 4-input OR gate
{
  return or_gate(or_gate(A, B), or_gate(C, D));
}

BIT or6_gate(BIT A, BIT B, BIT C, BIT D, BIT E, BIT F) // 6-input OR gate
{
  return or_gate(or_gate(A,F), or4_gate(B, C, D, E));
}

BIT and3_gate(BIT A, BIT B, BIT C) // 3-input AND gate
{
  return and_gate(and_gate(A, B), C);
}

BIT and4_gate(BIT A, BIT B, BIT C, BIT D) // 4-input AND gate
{
  return and_gate(and_gate(A, B), and_gate(C, D));
}

// END AND/OR SIMPLIFICATIONS

BIT xor_gate(BIT A, BIT B)
{
  // TODO: implement logical XOR
  return or_gate(and_gate(A, not_gate(B)), and_gate(not_gate(A), B));
}

BIT nor_gate(BIT A, BIT B)
{
  // TODO: implement logical NOR
  return not_gate(or_gate(A, B));
}

void decoder2(BIT I0, BIT I1, BIT* O0, BIT* O1, BIT* O2, BIT* O3)
{
  // TO DO: implement a 2-input decoder
  *O0 = and_gate(not_gate(I0), not_gate(I1));
  *O1 = and_gate(not_gate(I0), I1);
  *O2 = and_gate(I0, not_gate(I1));
  *O3 = and_gate(I0, I1);
}

BIT multiplexor2(BIT S, BIT I0, BIT I1)
{
  // TODO: implement a 2-input multiplexor
  return or_gate(and_gate(not_gate(S), I0), and_gate(S, I1));
}

BIT multiplexor4(BIT S0, BIT S1, BIT I0, BIT I1, BIT I2, BIT I3)
{
  // TODO: implement a 4-input multiplexor
  return or4_gate(
    and_gate(I0, and_gate(not_gate(S0), not_gate(S1))),
    and_gate(I1, and_gate(not_gate(S0), S1)),
    and_gate(I2, and_gate(S0, not_gate(S1))),
    and_gate(I3, and_gate(S0, S1))
  );
  // Boolean Algebra for 4-Mux
  // return (I0 && !S0 && !S1) || (I1 && !S0 && S1) || (I2 && S0 && !S1) || (I3 && S0 && S1);
}


/******************************************************************************/
/* Additional Functions that you will implement */
/******************************************************************************/
void convert_to_binary(int a, BIT* A)
{
  // TODO: convert integer to 2's complement BIT representation
  // Note: A[0] is least significant bit and A[31] is most significant bit
  // For this function ONLY: you're allowed to use logical if-else statements
  // and for loops or whatever else you need. The standard assignment rules do
  // not apply.
  
  // Convert base 10 "a" into 2's complement binary
  BIT neg = 0;
  if (a < 0) {
    a *= -1;
    neg = 1;
  }

  int i = 0;
  // Get little-endian magnitude
  for(; i < 32; i++){
    A[i] = a % 2;
    a = a / 2;
    if (a == 0) {break;}
  } 
  if(neg == 1){
    // Get 1-s complement
    for(int j = 0; j < 32; j++){
      A[j] = not_gate(A[j]);
    }
    // Get 2-s complement
    BIT carry = 1;
    for(int j = 0; j < 32; j++){
      if(carry == 1){
        if (A[j] == 0) {
           carry = 0;
           A[j] = 1;
        } else {
          A[j] = 0;
        }
      }
    }
  }
}

void shifter(BIT* A, BIT* R, BIT Control) { 
  // TODO: implement 1-bit shifter
  // One call to this circuit will shift A one bit to the left or right
  // The result will be stored in R
  // Control = 0 -> shift left
  // Control = 1 -> shift right
  // See: https://www.101computing.net/binary-shifters-using-logic-gates/
  BIT Not_Control = not_gate(Control);
  R[0] = and_gate(A[1], Control);
  for(int i = 1; i < 31; i++){
    R[i] = or_gate(and_gate(A[i+1], Control), and_gate(A[i-1], Not_Control));
  }
  
  R[31] = and_gate(A[30], Not_Control);
}

void left_shifter32(BIT* A, BIT* B, BIT* R)
{
  // TODO: Implement 32-bit left shifter
  // You'll shift input A to the left by the number specific in B
  // The result will be stored in R
  // You can assume that B >= 0
  // There's no specified circuit that you need to implement here. The logic
  // that I used for my implementation was basically:
  // B_temp = B, A_temp = A
  // for i = 0..31
  //   use ALU to check if B_temp < 1
  //   do left shift
  //   use mux to store A_temp in R if the result from above was false
  //   subtract 1 from B_temp using ALU
  // Note that this for loop is static, so allowed per our rules.
  copy_bits(A, R);
  BIT A_temp[32] = {FALSE};
  BIT B_temp[32] = {FALSE};
  copy_bits(A, A_temp);
  copy_bits(B, B_temp);
  BIT One[32] = {FALSE};
  convert_to_binary(1, One);
  //convert_to_binary(1, One);
  for(int i = 0; i < 2; i++){
    // use ALU to check if B_temp < 1
    BIT Res[32] = {FALSE};
    BIT Shift[32] = {FALSE};
    BIT Carryout = 0;
    // Check if B_temp - 1 < 0;
    ALU32(B_temp, One, 1, 1, 1, 1, Res, &Carryout);
    // We can shift left and if LT false, then we can store bitwise in R with a mux
    shifter(A_temp, Shift, 0);
    copy_bits(Shift, A_temp);
    for(int j = 0; j < 32; j++){
      R[j] = multiplexor2(Res[0], A_temp[j], R[j]);
    }
    // subtract 1 from B_temp using ALU
    ALU32(B_temp, One, 1, 1, 1, 0, B_temp, &Carryout);
  }
}


void multiplier16(BIT* A, BIT* B, BIT* R)
{  
  // TODO: Implement 16-bit multiplier
  // S = A * B
  // You can assume A and B are both less than 2^16
  // This should work regardless if A and B are positive/negative
  // See the diagram on slide 49 of Chapter-3d
  // - You can use your 32-bit ALU here for addition
  // - You can use your shifter as well for R/L shifts
  // - For 'control', you are allowed to use a for loop
  BIT carryout= 0;
  BIT alures[32] = {FALSE};
  BIT TmpA[32] = {FALSE};
  BIT TmpB[32] = {FALSE};
  copy_bits(A, TmpA);
  copy_bits(B, TmpB);
  BIT Tmp[32] = {FALSE};
  for(int i = 0; i < 16; i++){
    // Each iteration:
    // If Multiplier[0] == 1, then add to Product
    //Shift Multiplicand left
    //Shift Multiplier right
    ALU32(R, TmpA, 0, 0, 1, 0, alures, &carryout);
    for (int j = 0; j < 32; j++){
      // IF multiplier[0] == 1, then add to product
      R[j] = multiplexor2(TmpB[0], R[j], alures[j]);
    }
    shifter(TmpA, Tmp, 0);
    copy_bits(Tmp, TmpA);
    shifter(TmpB, Tmp, 1);
    copy_bits(Tmp, TmpB);
  }  
}

void adder1(BIT A, BIT B, BIT CarryIn, BIT* CarryOut, BIT* Sum) {
  // TODO: implement a 1-bit adder
  *Sum = xor_gate(xor_gate(A, B), CarryIn);
  *CarryOut = or_gate(and_gate(A, B), and_gate(CarryIn, xor_gate(A, B)));
  return;
}

void ALU1(BIT A, BIT B, BIT Binvert, BIT CarryIn, BIT Less, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut, BIT* Set) {
  // Note: this will need modifications from Lab 5 to account for 'slt'
  // See slide 30 in Chapter-3d
  // TODO: implement a 1-bit ALU 
  // result = 2mux( op0 && op1, alu output, false)
  // alu output = 4mux( op0, op1, a && b, a || b, a + b, less)
  // a + b == adder(a,b,carryin, carryout, sum)
  B = multiplexor2(Binvert, B, not_gate(B));
  adder1(A, B, CarryIn, CarryOut, Result);
  *Set = *Result;   
  *Result = multiplexor4(Op0, Op1, and_gate(A, B), or_gate(A, B), *Result, Less);
  return;
}


void ALU32(BIT* A, BIT* B, BIT Binvert, BIT CarryIn, 
  BIT Op0, BIT Op1, BIT* Result, BIT* CarryOut) {
  // TODO: implement a 32-bit ALU
  // You'll need to essentially implement a 32-bit ripple addder here
  // See slide 31 in Chapter-3d
  BIT Set = 0;
  BIT Less = 0;
  for(int i = 0; i < 32; i++){
    // NOTE: LESS = 0 for all, then redo lsb with less = set of msb
    ALU1(A[i], B[i], Binvert, CarryIn, Less, Op0, Op1, &Result[i], CarryOut, &Set);
    CarryIn = *CarryOut;
  }
  // Set MSB = Less LSB, then output that to Result[0] if Op0 && Op1
  Result[0] = multiplexor2(and_gate(Op0, Op1), Result[0], Set);
}


void Control(BIT* A, BIT* B, BIT* OP, BIT* Result) 
{
  // The will be the control circuit for all of our ALU operations
  // You will do some specified operation between A and B and store the final 
  // output into Result
  // One difficulty might be in converting our 3-bit OP input to the 2-bit
  // control for the ALU. You can use SOP circuits for this.
  // For my implementation, I compute 4 results here and use a 4-mux to get
  // the final Result:
  //  1. Output from ALU (and, or, add, sub, slt)
  //  2. Logical nor (using output from ALU)
  //  3. Left shift
  //  4. Multiplication
  // You can use this approach or any other that you can come up with, as long
  // as it is representative of an implementable circuit.
  // Note: be careful with your multiplication and shifter circuits. You can 
  // create/copy temporary 32-bit binary values as often as necessary. Just make
  // sure you haven't overwritten the A, B inputs before you return to main.
  BIT andbit  = and3_gate(not_gate(OP[2]), not_gate(OP[1]), not_gate(OP[0]));
  BIT orbit   = and3_gate(not_gate(OP[2]), not_gate(OP[1]), OP[0]);
  BIT norbit  = and3_gate(not_gate(OP[2]), OP[1], not_gate(OP[0]));
  BIT addbit  = and3_gate(not_gate(OP[2]), OP[1], OP[0]); 
  BIT subbit  = and3_gate(OP[2], not_gate(OP[1]), not_gate(OP[0]));
  BIT sltbit  = and3_gate(OP[2], not_gate(OP[1]), OP[0]);
  BIT shftbit = and3_gate(OP[2], OP[1], not_gate(OP[0]));
  BIT alubit  = or6_gate(andbit, orbit, norbit, addbit, subbit, sltbit);
  BIT op0 = 0;
  BIT op1 = 0;
  BIT binvert = 0;
  BIT carryin = 0;
  BIT carryout = 0;
  // op0 = 1 when + or - or <
  // op1 = 1 when || or <
  // binvert = 1 when - or slt
  // carryin = 1 when - or slt
  op0 = multiplexor2(or3_gate(addbit, subbit, sltbit), 0, 1);
  op1 = multiplexor2(or3_gate(orbit, sltbit, norbit), 0, 1);
  binvert = multiplexor2(or_gate(subbit, sltbit), 0,  1);
  carryin = multiplexor2(or_gate(subbit, sltbit), 0, 1);
  BIT alures[32]  = {FALSE};
  BIT shftres[32] = {FALSE};
  BIT mulres[32]  = {FALSE};
  // Set up SLT
  binvert = multiplexor2(or_gate(sltbit, and_gate(subbit, B[31])), 0, 1);
  carryin = multiplexor2(or_gate(sltbit, and_gate(subbit, B[31])), 0, 1);
  ALU32(A, B, binvert, carryin, op0, op1, alures, &carryout);
  left_shifter32(A, B, shftres);
  multiplier16(A, B, mulres);
  //Bitwise for results
  for(int i = 0; i < 32; i++){
    BIT tmp = multiplexor4(alubit, shftbit, mulres[i], shftres[i], alures[i], FALSE);
    Result[i] = multiplexor2(norbit, tmp, not_gate(tmp));
  }
  
  

}

/******************************************************************************/
/* Main */
/******************************************************************************/
int main()
{
  // Read in our operands and operation
  int a = 0;
  int b = 0;
  char op = '\0';
  scanf("%d %c %d", &a, &op, &b);  
  
  // Do our necessary converstions
  BIT A[32] = {FALSE};
  BIT B[32] = {FALSE};
  BIT R[32] = {FALSE};
  convert_to_binary(a, A);
  convert_to_binary(b, B);
  // Set our OP bits for the operation
  BIT OP[3] = {FALSE};
  set_op(op, OP);
  
  // Call our control circuit to do the business
  Control(A, B, OP, R);
  
  // Output our result
  print_binary(A);
  printf("\n%c\n", op);
  print_binary(B);
  printf("\n=\n");
  print_binary(R);
  
  return 0;
}

