#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>


// Output the right triangle using nested loops
int output_triangle_nested_loops(int n)
{
  // Use nested for loops and printf to output the appropriate triangle
  for (int col = 1; col < n+1; col++){
    for (int row = 0; row < 2 * n - 1; row++){
      if (row < 2 * n - 1 - col){
        printf(" ");
      }
      else{
        printf("*");
      }
    }
    printf("\n");
  }

  return 0;
}


// Calculate the length of the hypotenuse for the output triangles
// Recall: a^2 = b^2 + c^2
// To compile with gcc, you will need to use the '-lm' flag
float calculate_hypotenuse(int n)
{
  // return the calculated hyponetuse length
  // Note: n = height of triangle, 2*n-1 is the width
  float hyp = pow(pow(n, 2) + pow(2 * n - 1, 2), 0.5);
  return hyp;
}

// Calculate Fibonacci number via recursion
long calc_fib_recursion(long n)
{
  // return either a recursive call or the fibonacci value
  if(n == 1) { return 0; }
  if(n == 2) { return 1; }
  return calc_fib_recursion(n - 1) + calc_fib_recursion(n - 2);
}

int main()
{
  int n;
  long f_n;

  printf("What is n? ");
  scanf("%d", &n);
  printf("%d\n", n);
  output_triangle_nested_loops(n);
  printf("Length of hypotenuse: %.2f\n", calculate_hypotenuse(n));

  printf("What is n? ");
  scanf("%li", &f_n);
  printf("%li\n", f_n);
  printf("Fibonacci: %li\n", calc_fib_recursion(f_n));
  
  return 0;
}
