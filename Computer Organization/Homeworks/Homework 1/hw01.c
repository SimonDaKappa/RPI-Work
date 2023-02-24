/* 
Assignment 1: NxM Matrix Multiplication 
CSCI-2500 Spring 2023
Prof. Slota 
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

/******************************************************************************/
/* Matrix struct and functions */
/******************************************************************************/

typedef struct{
  double** data;
  int num_rows;
  int num_cols;
} matrix; 

int mm_alloc(matrix* mat);
int mm_free (matrix* mat);
int mm_print(matrix* mat);
int mm_read (char* filename, matrix* mat);
matrix* mm_matrix_mult(matrix* mat1, matrix* mat2);
matrix* mm_matrix_transpose(matrix* mat1);

/******************************************************************************/
/* Function Calls - Fill in all of the below */
/******************************************************************************/

int mm_alloc(matrix* mat)
{
/*
Notes:
  Allocate an array of pointers to arrays of doubles
  Then, allocate a row/array of doubles and assign a pointer that row
  Make sure you're allocating using mat->data in the matrix struct
  You can use calloc for allocation and zeroing out all the bytes
  - otherwise, you'd want to manually set all arrays to 0 (good practice)
  If your malloc/calloc returns null, the allocation failed
*/

  if(mat->num_rows < 1 || mat->num_cols < 1){
    printf("mm_alloc: allocation failed.\n");
    exit(-1);
  }
  // Used calloc here so values are initialized
  mat->data = (double **)calloc(mat->num_rows, sizeof(double *));
  for (int i = 0; i < mat->num_rows; i++)
  {
    mat->data[i] = (double*)calloc(mat->num_cols, sizeof(double));
  }
  return 0;
}

int mm_free(matrix* mat)
{
  /*
  Notes:
  Reverse the allocation process, but you'll be calling free() instead
  */
  for (int i = 0; i < mat->num_rows; i++){
    free(mat->data[i]);
  }
  free(mat->data);
  return 0;
}

int mm_print(matrix* mat)
{
/*
Notes:
  This function will print all the data values in your matrix
  Go row by row, printing all the values in a matrix row
  At the end of each row, print a newline
  Between each data value within a row, insert a tab. Also use 2 digits of 
    precision after the decimal ("%10.2lf\t" is the format string)
  See output.txt for expected output formatting
*/
  printf("\n/******** START of 2-D Matrix ********************************/\n");
  for (int i = 0; i < mat->num_rows;++i){
    for (int j = 0; j < mat->num_cols; ++j){
      printf("%10.2lf\t", mat->data[i][j]);
    }
    printf("\n");
  }
  printf("/******** END of 2-D Matrix **********************************/\n");
  return 0;
}

int mm_read(char* filename, matrix* mat) 
{
  /*
  Notes:
    Use fopen to open the matrix file, then use fgets or getline to read lines
    The first line of the matrix contains integers for "#rows #columns"
    - Use these to allocate your arrays for matrix data
    Each subsequent line contains a row of values for the matrix
    - You can assume that each line in the file has fewer than 256 characters
    - You can use sscanf to parse each matrix entry
    - First value is data[0][0], next is data[0][1] 
    - Next row has data[1][0], data[1][1], ..., data[1][#columns-1]
    - ... data[#rows-1][#columns-1]
    */
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("mm_read: failed to open file.\n");
    exit(-1);
  }
  int line_num = 0;
  char line[256];
  while (1) {
    // Get line from file
    fgets(line, 256, fp);
    if (line == NULL) { break; }
    if(line_num == 0){
      line_num++;
      // set mat->num_rows and mat->num_cols from line 0
      if(2!= sscanf(line, "%d %d", &mat->num_rows, &mat->num_cols)) {
        printf("mm_read: failed to read from file.\n");
        exit(-1);
      }
      mm_alloc(mat);
    }
    else{
      if(line_num > mat->num_rows) { break; }
      // read in one row of the matrix from file
      char *data = line;
      // Without Offset, will put first value into entire row
      int offset;
      for (int i = 0; i < mat->num_cols; i++) {
        if (1 != sscanf(data, "%lf %n", &mat->data[line_num - 1][i], &offset)) {
          printf("mm_read: failed to read from file.\n");
          exit(-1);
        }
        data += offset;
      }
      line_num++;
    }
  }
  fclose(fp);
  return 0;
}

matrix* mm_matrix_mult(matrix* mat1, matrix* mat2)
{
  /*
  Notes:
    First check that it is actually possible to multiply the two inputs
    If so, construct a result matrix. Note that you'll also need to initialize
      and allocatge the matrix struct as well.
    Then perform the multiplication.
    Return a pointer to your result matrix
  */

  // Dimension Error Handling
  if(mat1->num_cols != mat2->num_rows){
    printf("mm_matrix_mult: dimension mismatch between matrices.\n");
    exit(-1);
  }

  // Result Matrix Construction/Allocation
  matrix* result_matrix = (matrix*)malloc(sizeof(matrix));
  result_matrix->num_rows = mat1->num_rows;
  result_matrix->num_cols = mat2->num_cols;
  mm_alloc(result_matrix);
  
  // Naive Mat Mult, Assumes small dimensions
  for(int i  = 0; i < mat1->num_rows; i++) {
    for(int j = 0; j < mat2->num_cols; j++) {
      for(int k = 0; k < mat1->num_cols; k++) {
        // Does dot term-wise instead of summing and adding sum later
        result_matrix->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
      }
    }
  }
  return result_matrix;
}

matrix* mm_matrix_transpose(matrix* mat1)
{
  /*
  Notes:
   This computes the matrix transpose of the input
   Result is returned 
  */
  // Create matrix of swapped dimensions
  matrix* result_matrix = (matrix*)malloc(sizeof(matrix));
  result_matrix->num_cols= mat1->num_rows;
  result_matrix->num_rows = mat1->num_cols;
  mm_alloc(result_matrix);

  // Transpose mat 
  for (int i = 0; i < mat1->num_rows; ++i) {
    for (int j = 0; j < mat1->num_cols; ++j) {
      result_matrix->data[j][i] = mat1->data[i][j];
    }
  }
  return result_matrix;
}


/******************************************************************************/
/* Main - leave the below unmodified */
/******************************************************************************/
int main()
{
  /*
   * you must keep this function AS IS. 
   * you cannot modify it!
   */
  char filename_A[256];
  char filename_B[256];
  matrix* A = (matrix*)malloc(sizeof(matrix));
  matrix* B = (matrix*)malloc(sizeof(matrix));
  matrix* C = NULL;
  matrix* D = NULL;

  printf("Please enter the matrix A data file name: ");
  if (1 != scanf("%s", filename_A)) {
    printf("main: scanf failed to read filename\n");
    exit(-1);
  }
  mm_read(filename_A, A);
  mm_print(A);
  
  printf("Please enter the matrix B data file name: ");
  if (1 != scanf("%s", filename_B)) {
    printf("main: scanf failed to read filename\n");
    exit(-1);
  }
  mm_read(filename_B, B);
  mm_print(B);
  
  printf("Performing multiplication operation.");
  C = mm_matrix_mult(A, B);
  mm_print(C);
  
  printf("Performing transpose operation.");
  D = mm_matrix_transpose(C);
  mm_print(D);

  mm_free(A);
  mm_free(B);
  mm_free(C);
  mm_free(D);
  free(A);
  free(B);
  free(C);
  free(D);
  
  return 0;
}
