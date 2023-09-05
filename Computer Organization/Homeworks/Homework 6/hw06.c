/* 
HW 6: Cache Rules Everything Around Us
CSCI-2500 Spring 2023
Prof. Slota 
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// maximum size of the input
#define MAX_ADDRESSES 1024
#define CACHE_SIZE 256

struct cacheInt{
  int value;
  int stepUsed;
};


/******************************************************************************/
/* Just doing everything in main */
/******************************************************************************/
int main(int argc, char** argv)
{
  // read associativity and set cache parameters

  // read memory addresses
  int count = 0;
  int associativity = atoi(argv[1]);
  int cacheSets = CACHE_SIZE / associativity;
  int addresses[MAX_ADDRESSES];
  int address;
  while (scanf("%d", &address) != EOF) {
    addresses[count] = address;
    count++;
  }  

  // allocate memory for cache structure
  struct cacheInt** cache = (struct cacheInt**)malloc(cacheSets * sizeof(struct cacheInt*));
  for(int i = 0; i < cacheSets; i++){
    cache[i] = (struct cacheInt*)malloc(associativity * sizeof(struct cacheInt));
  }

  // initialize cache to 0
  for(int i = 0; i < cacheSets; i++){
    for(int j = 0; j < associativity; j++){
      struct cacheInt tmp = {0, 0};
      cache[i][j] = tmp;
    }
  }

  // preliminary output
  printf("Cache size: 256\n");
  printf("Cache associativity: %d\n", associativity);
  printf("Cache sets: %d\n", cacheSets);

  // run the simulation
  int hits = 0;
  int misses = 0;
  int step = 0;
  for(int i  = 0; i < count; i++){
    int set = addresses[i] % cacheSets;
    printf("%d ", addresses[i]);

    // Loop through the set to see if we already have hit
    int hitfound = 0;
    for(int j = 0; j < associativity; j++){
      hitfound = 0;
      // If hit is found 
      if (cache[set][j].value == addresses[i]){
        printf("(hit)\n");
        hitfound = 1;
        hits++;
        break;
      }
    }
    // If no hit found, add to set and update stepUsed
    if(hitfound == 0){
      printf("(miss)\n");
      int roomfound = 0;
      // If room, add to next empty entry
      for(int k = 0; k < associativity; k++){
        if(cache[set][k].value == 0){
          cache[set][k].value = addresses[i];
          cache[set][k].stepUsed = step;
          roomfound = 1;
          misses++;
          break;
        }
      }
      // If set is full, replace the smallest stepUsed entry
      if(roomfound == 0){   
        int smallestIdx = 0;
        for(int l = 0; l < associativity; l++){
          if(cache[set][l].stepUsed < cache[set][smallestIdx].stepUsed){
            smallestIdx = l;
          }
        }
        cache[set][smallestIdx].value = addresses[i];
        cache[set][smallestIdx].stepUsed = step;
        misses++;
      }
    }
    step++;
  }

  // output final statistics
  printf("Cache accesses: %d\n", count);
  printf("Cache hits: %d\n", hits);
  printf("Cache misses: %d\n", misses);
  printf("Overall hit rate: %f\n", ( hits + 0.0 ) / count);

  // clean up memory
  for(int i = 0; i < associativity; i++){
    free(cache[i]);
  }
  free(cache);
  return 0;
}
