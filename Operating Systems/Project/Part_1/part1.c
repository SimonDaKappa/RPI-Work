#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define MAX_RNG_ITERATIONS 100
#define TRUE 1
#define FALSE 0

struct Process
{
  char pid;
  bool cpu_bound;
  int arrival_time;
  int cpu_burst_count;
  int cpu_burst_time;
  int io_burst_time;
  int turnaround_time;
  int wait_time;
  float cpu_utilization;
};


void parse_arguments(int argc, char** argv, int* num_processes, int* num_cpu_bound, int* rng_seed, float* avg_arrival_scale, float* arrival_upper_bound) {
  if (argc != 6 || argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[4] == NULL || argv[5] == NULL) {
    fprintf(stderr, "ERROR: Invalid input arguments\n");
    printf("Usage: %s <num_processes> <num_cpu_bound> <rng_seed> <avg_arrival_scale> <arrival_upper_bound>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  *num_processes = atoi(argv[1]);
  *num_cpu_bound = atoi(argv[2]);
  *rng_seed = atoi(argv[3]);
  *avg_arrival_scale = atof(argv[4]);
  *arrival_upper_bound = atof(argv[5]);
}


double next_exp(float avg_scale, float upper_bound){
#ifdef DEBUG
  printf("next_exp(avg_scale=%f, upper_bound=%f):\n", avg_scale, upper_bound);
#endif

  int iterations = 0;
  while(iterations++ < MAX_RNG_ITERATIONS){
    double r = drand48();
    double x = -log(r) / avg_scale;
#ifdef DEBUG
    printf("DEBUG: Random number: %f\n", r);
    printf("DEBUG: Random number (log): %f\n", log(r));
    printf("DEBUG: Random number (exp): %f\n", -log(r));
    printf("DEBUG: Random number (exp) / avg_scale: %f\n", x);
#endif
    if (x <= upper_bound) {
      return x;
    }
  }
  return -1;
}

int main(int argc, char **argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);
  typedef struct Process Process;
  int num_processes, num_cpu_bound, rng_seed;
  float avg_arrival_scale, arrival_upper_bound, avg_scale, upper_bound;
  parse_arguments(argc, argv, &num_processes, &num_cpu_bound, &rng_seed, &avg_arrival_scale, &arrival_upper_bound);
  avg_scale = avg_arrival_scale;
  upper_bound = arrival_upper_bound;
  srand48(rng_seed);

#ifdef DEBUG
  printf("DEBUG: Number of processes: %d\n", num_processes);
  printf("DEBUG: Number of CPU bound processes: %d\n", num_cpu_bound);
  printf("DEBUG: Random number generator seed: %d\n", rng_seed);
  printf("DEBUG: Average arrival time: %f\n", avg_arrival_scale);
  printf("DEBUG: Arrival upper bound: %f\n", arrival_upper_bound);
#endif

  printf("<<< PROJECT PART I -- process set (n=%d) with %d CPU-bound process%s >>>\n", 
    num_processes, num_cpu_bound, (num_cpu_bound==1) ? "" : "es" );
  Process* processes = (Process*)malloc(num_processes * sizeof(Process));

  // Init processes
  for (int i = 0; i < num_processes; i++) {
    processes[i].pid = (char)(i + 65);
    processes[i].cpu_bound = ((num_processes - i) <= num_cpu_bound);
    processes[i].cpu_burst_time = 0;
    processes[i].io_burst_time = 0;
    processes[i].turnaround_time = 0;
    processes[i].wait_time = 0;
    processes[i].cpu_utilization = 0.0;
    
  }

#ifdef DEBUG
  printf("DEBUG: Processes:\n");
  for (int i = 0; i < num_processes; i++) {
    printf("DEBUG: Process %c: %s\n", processes[i].pid, (processes[i].cpu_bound) ? "CPU-bound" : "I/O-bound");
  }
#endif

  // Start basic simulation
  for (int i = 0; i < num_processes; i++) {
    Process process = processes[i];
    process.arrival_time = (int)floor(next_exp(avg_arrival_scale, arrival_upper_bound));
    process.cpu_burst_count = (int)ceil(drand48() * 64);
    
    printf("%s-bound process %c: arrival time %dms; %d CPU bursts:\n", 
      (process.cpu_bound) ? "CPU" : "I/O", 
      process.pid, process.arrival_time, 
      process.cpu_burst_count
    );

        // iterate bursts for current process
    for (int j = 0; j < process.cpu_burst_count; j++)
    {
      int current_cpu_burst, current_io_burst;
  
      current_cpu_burst  = (int) ceil(next_exp(avg_scale, upper_bound));
      current_cpu_burst *= (process.cpu_bound) ? 4 : 1;
      
      if (j < process.cpu_burst_count - 1)
      {
        current_io_burst = (int)ceil(next_exp(avg_scale, upper_bound)) * 10;
        current_io_burst /= (process.cpu_bound) ? 8 : 1;g
        printf("--> CPU burst %dms --> I/O burst %dms\n", current_cpu_burst, current_io_burst);
      }
      else
      {
        printf("--> CPU burst %dms\n", current_cpu_burst);
      }
    }
  }

  free(processes);
  return EXIT_SUCCESS;
}