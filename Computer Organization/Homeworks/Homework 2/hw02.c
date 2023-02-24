/* 
Assignment 2: I was born an assemblin' man,
              Tryin' to make a compiler, and doin' the best I can.
CSCI-2500 Spring 2023
Prof. Slota 
*/

/******************************************************************************/
/* Usual suspects to include */
/* Include anything else you want from the C standard library */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/******************************************************************************/
/* You can construct as many additional helper functions as you wish */
/* Note: You don't need to call this throw_error() function, can exit in main */
/******************************************************************************/

struct token {
  char *token_val;  // The token itself
  int token_type;   // 0 = c-variable, 1 = assignment operator, 2 = integer, 3 = operator
  int token_idx;    // The index of the token in the line
  int token_reg;    // The s register the token is "stored in"
};

void throw_error(){
  fprintf(stderr, "Parsing error...\n");
  exit(-1);
}


int is_valid_identifier(struct token* tok, int total_tokens){
  int idx = tok->token_idx;

  if (idx == 0){
    // 0th token must be a c-variable
    if(strlen(tok->token_val) != 1 || !isalpha(tok->token_val[0]))
      return 0;
    tok->token_type = 0;
    return 1;
  }
  else if(idx == 1){
    // 1st token must be a assignment operator
    if(strcmp(tok->token_val, "=") != 0)
      return 0;
    tok->token_type = 1;
    return 1;
  }
  else if(idx % 2 == 0){
    if (idx == total_tokens){
      // Last index token must be a c-variable/integer ending in ';' (thus min length is 2)
      if(strlen(tok->token_val) == 1 || tok->token_val[strlen(tok->token_val) - 1] != ';')
        return 0;
      else{
        //Must be a single type
        if(isalpha(tok->token_val[0])){} // Type is c-variable
          if(strlen(tok->token_val > 2))
            return 0;
          tok->token_type = 0;
        if(isdigit(tok->token_val[0])) // Type is integer
          tok->token_type = 2;
        for (int i = 0; i < strlen(tok->token_val) - 1; i++){
          if(tok->token_type == 0 && !isalpha(tok->token_val[i]))
            return 0;
          if(tok->token_type == 2 && !isdigit(tok->token_val[i]))
            return 0;
        }
        tok->token_val[strlen(tok->token_val) - 1] = '\0'; // Strip off ';'
        return 1;
      }
    }
    // Non-Last Even tokens must be a c-variable/integer
    else{
      if(strlen(tok->token_val) == 1){
        // Must be a single digit or char
        if(isalpha(tok->token_val[0])){
          tok->token_type = 0;
          return 1;
        }
        if(isdigit(tok->token_val[0])){
          tok->token_type = 2;
          return 1;
        }
        else
          return 0;
      }
      // Longer than 1
      else{
        // Must be a integer
        if(isalpha(tok->token_val[0])) // Type is c-variable
          return 0;
        if (isdigit(tok->token_val[0])) // Type is integer
          tok->token_type = 2;
        for (int i = 0; i < strlen(tok->token_val); i++){;
          if(tok->token_type == 2 && !isdigit(tok->token_val[i]))
            return 0;
        }
        return 1;
      }
    }
  }
  else if(idx % 2 == 1){
        // Odd index tokens must be an operator
        if(strcmp(tok->token_val, "+") == 0 || strcmp(tok->token_val, "-") == 0){
          tok->token_type = 3;
          return 1;
        }
        else
          return 0;
  }
  // Should never be reached, i think my ruleset is complete
  return -1;
}

/******************************************************************************/
/* Our main function. */  
/* Note: we're now outputting errors to stderr  */
/******************************************************************************/
int main( int argc, char * argv[] )
{
  char line[256];
  printf("Please enter a valid C assignment statement:\n");
  if (fgets(line, 256, stdin) == NULL) {
    fprintf(stderr, "fgets() failed");
    exit(-1);
  }
  line[strcspn(line, "\n")] = 0; // Remove trailing \n from line
  
  
  // Create token array of >> size than token count
  // There are at most 18 registers, so 36 is plenty
  struct token* token_array = malloc(sizeof(struct token) * 36);
  // Find total token count 
  int token_count = 0;
  char *token = strtok(line, " ");

  while(token != NULL){
    // Create token struct for each token (type will be determined later)
    token_array[token_count].token_val = token;
    token_array[token_count].token_idx = token_count;

    token = strtok(NULL, " ");
    if(token != NULL)
      token_count++;
  }

  // A valid assignment has even amount of tokens (starting at 0) and at minimum 2 tokens
  // (0 - cvar, 1 - assignment, 2 - cvar/int)
  if(token_count % 2 == 1 || token_count < 2)
    throw_error();

  // Realloc token array to exact size
  token_array = realloc(token_array, sizeof(struct token) * (token_count + 1));

  // Validate each token and assign register (if neccesary)
  int s_reg_counter = 0;
  for (int i = 0; i <= token_count; i++){
    
    int valid = is_valid_identifier(&token_array[i], token_count);
    if(valid == 0 || valid == -1)
      throw_error();
    
    if(token_array[i].token_type == 0){
      int match = 0;
      // Check for duplicate c-variables, if found, assign same register
      for (int j = 0; j < i; j++){
        if(strcmp(token_array[i].token_val, token_array[j].token_val) == 0){
          token_array[i].token_reg = token_array[j].token_reg;
          match = 1;
          break;
        }
      }
      if(match == 0)
        token_array[i].token_reg = s_reg_counter++;
    }
  }


  // MIPS Translation
  printf("The MIPS pseudocode is:\n");
  
  // Single Assignment 
  if(token_count == 2){
    printf("add $s0,");
    if (token_array[2].token_type == 0)
      printf("$s1,0\n");
    else
      printf("%s,0\n", token_array[2].token_val);
  }

  // Operations + Assignment
  else{
    int t_counter = 0;
    int t_counter2 = 0;
    for (int i = 2; i <= token_count - 2; i += 2)
    {

      // Instruction
      if (strcmp(token_array[i + 1].token_val, "+") == 0)
        printf("add ");
      else if (strcmp(token_array[i+1].token_val, "-") == 0)
        printf("sub ");
      
      // First Register in Instruction
      if(i == token_count-2)
        printf("$s0,");
      else
        printf("$t%d,", t_counter++);

      // Second Register in Instruction
      if(i == 2){
        if (token_array[i].token_type == 0)
          printf("$s%d,", token_array[i].token_reg);
        else
          printf("%s,", token_array[i].token_val);
      }
      else{
        printf("$t%d,", t_counter2++);
      }

      // Third Register in Instruction
      if(token_array[i+2].token_type == 0)
        printf("$s%d\n", token_array[i+2].token_reg);
      else
        printf("%s\n", token_array[i+2].token_val);
    }
  }

  free(token_array);
  return 0;
}

