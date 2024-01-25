#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#define TRUE 1
#define FALSE 0

int SumAscii(char* str){
  int sum = 0;
  for (size_t i = 0; i < strlen(str); i++){
    sum += (int) *(str + i);
  }
  return sum;
}

int getNextWord(FILE* file, char* word){
  // word is 128bytes long!
  char current_char;
  uint8_t current_char_index = 0;
  while ((current_char = fgetc(file)) && current_char != EOF && current_char_index < 128)
  {
    if (isalnum(current_char)){
      *(word + current_char_index) = current_char;
      current_char_index++;
      continue;
    }
    else {
      return TRUE;
    }
  }
  return FALSE;
}

int main(int argc, char **argv)
{

#ifdef DEBUG
  printf("argc: %d\n", argc);
  for (int i = 0; i < argc; i++){
    printf("*argv+%d: %s\n", i, *(argv+i));
  }
#endif

  if (argc != 3){
    fprintf(stderr, "ERROR: Usage: %s <cache size> <input file path>\n", *argv);
    return EXIT_FAILURE;
  }

  // Verify first argument is a number
  for (size_t i = 0; i < strlen(*(argv+1)); i++){
    if (!isdigit(*(*(argv+1)+i))){
      fprintf(stderr, "ERROR: First argument must be a number\n");
      return EXIT_FAILURE;
    }
  }


  int cache_size = atoi(*(argv+1));  
  char* file_path = *(argv+2);

#ifdef DEBUG
  printf("Cache size: %d\nFile path: %s\n", cache_size, file_path);
#endif

  // Open file
  FILE* file = fopen(file_path, "r");
  if (file == NULL){
    fprintf(stderr, "ERROR: Could not open file \"%s\"\n", file_path);
    return EXIT_FAILURE;
  }

  // Initialize string cache
  char** cache = (char**) calloc(cache_size, sizeof(char*));
  char* word = calloc(128, sizeof(char));
  int word_len, word_sum, cache_index = 0;
  while (getNextWord(file, word) == TRUE)
  {
    if (word == NULL || strlen(word) < 3 || strlen(word) > 128){
      continue;
    }

#ifdef DEBUG
    printf("Word: %s\n", word);
#endif

    word_sum = SumAscii(word);
    word_len = strlen(word);
    cache_index = word_sum % cache_size;

    if (*(cache + cache_index) == NULL){  
      // Add word to cache
      *(cache + cache_index) = (char*) calloc(word_len + 1, sizeof(char));
      strcpy(*(cache + cache_index), word);
      printf("Word \"%s\" ==> %d (calloc)\n", word, cache_index);
    }
    else {
      // Replace word in cache
      *(cache + cache_index) = (char*) realloc(*(cache + cache_index), word_len + 1);
      strcpy(*(cache + cache_index), word);
      printf("Word \"%s\" ==> %d (realloc)\n", word, cache_index);
    }

    memset(word, 0, 128);
  }

  for (int i = 0; i < cache_size; i++){
    if (*(cache + i) != NULL){
      printf("Cache index %d ==> \"%s\"\n", i, *(cache + i));
      free(*(cache + i));
    }
  }

  free(word);
  free(cache);
  fclose(file);
  return EXIT_SUCCESS;
}