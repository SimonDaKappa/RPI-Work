/* 
Lab 7: Living in a Parallel Universe
CSCI-2500 Spring 2023
Prof. Slota 
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


/******************************************************************************/
/* Primary code. Fill in the TODOs to get credit. */
/******************************************************************************/
int* parallel_copy(int* array, int length)
{
  int* array2 = malloc(length*sizeof(int));
  
#pragma omp parallel for
  for (int i = 0; i < length; ++i)
    array2[i] = array[i];
  
  return array2;
}

int compute_sum(int* array, int length)
{
  double elt = omp_get_wtime();
  
  int sum = 0;
  // TODO: compute the sum of the input array in serial
  for(int i = 0; i < length; i++)
    sum += array[i];
  
  printf("Sum time: %lf seconds\n", omp_get_wtime() - elt);
  return sum;
}

int compute_parallel_sum(int* array, int length)
{
  double elt = omp_get_wtime();
  
  int sum = 0;
  // TODO: compute the sum of the input array in parallel
  // Note: You must use OpenMP pragmas to do this parallelization
  #pragma omp parallel for reduction(+:sum) 
  for (int i = 0; i < length; ++i)
    sum += array[i];
  
  printf("Parallel sum time: %lf seconds\n", omp_get_wtime() - elt);
  return sum;
}

int* compute_prefix_sums(int* array, int length)
{
  double elt = omp_get_wtime();
  
  // See below for the basic serial prefix sums calculation
  int* prefix_sums = malloc(length*sizeof(int));
  prefix_sums[0] = array[0];
  
  for (int i = 1; i < length; ++i)
    prefix_sums[i] = prefix_sums[i-1] + array[i];
  
  printf("Prefix sum time: %lf seconds\n", omp_get_wtime() - elt);
  array = parallel_copy(prefix_sums, length);
  free(prefix_sums);
  return array;
}

int* compute_parallel_prefix_sums(int* array, int length)
{
  double elt = omp_get_wtime();
  
  int* prefix_sums = malloc(length*sizeof(int));
  prefix_sums = parallel_copy(array, length);
  // TODO: implement any one of the parallel prefix sums algorithms
  for(int i = 1; i < length; i*=2){
    int *tmp_presum = parallel_copy(prefix_sums, length);
    
    #pragma omp parallel for 
    for (int j = 0; j < length; j++)
    {
      if (j < i)
        prefix_sums[j] = tmp_presum[j];
      else
        prefix_sums[j] = tmp_presum[j - i] + tmp_presum[j];
    }
    free(tmp_presum);
  }
  printf("Parallel prefix sum time: %lf seconds\n", omp_get_wtime() - elt);
  array = parallel_copy(prefix_sums, length);
  free(prefix_sums);
  return array;
}



/******************************************************************************/
/* main -- you might need to modify this for I/O */
/******************************************************************************/
int main()
{
  omp_set_num_threads(4);
  int array[1024*1024] = {0};
  int length = 0;
  while (scanf("%d", &array[length]) > 0)
    ++length;
  
  int* copy = parallel_copy(array, length);
  free(copy);
  
  int serial_sum = compute_sum(array, length);
  int parallel_sum = compute_parallel_sum(array, length);
  printf("Serial sum: %d\n",  serial_sum);
  printf("Parallel sum: %d\n",  parallel_sum);
  if (serial_sum != parallel_sum)
    printf("ERROR: Divergent values in summation.\n");

  int* ps1 = compute_prefix_sums(array, length);
  int* ps2 = compute_parallel_prefix_sums(array, length);
  for (int i = 0; i < length; ++i) {
    if (ps1[i] != ps2[i]) {
      printf("ERROR: Divergent values in prefix sums:\n");
      printf("  index %d: serial = %d, parallel = %d\n", i, ps1[i], ps2[i]);
    }
  } 
  return 0;
}