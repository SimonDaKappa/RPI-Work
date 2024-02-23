#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_CMD  1024 // Maximum length of a line
#define MAX_ARG  64   // Maximum Length of arguments
#define MAX_ARGS 16   // Maximum number of arguments
#define MAX_BGP  16   // Maximum number of background processes
#define TRUE     1
#define FALSE    0
#define SUCCESS  1
#define FAILURE  0


int arrayLength(char* array[]){
  int i = 0;
  while(array[i] != NULL){
    i++;
  }
  return i;
}


void exitShell(){
  printf("bye\n");
  exit(EXIT_SUCCESS);
}


void printWorkingDirectory(){
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
#ifdef DEBUG
  printf("DEBUG: Current working directory: \n%s$ ", cwd);
#else
  printf("%s$ ", cwd);
#endif
}


int pipeIndex(char* command){
  // RETURN PIPE_IDX == -1 IF NO PIPE
  for(size_t i = 0; i < strlen(command); i++){
    if(command[i] == '|'){
      return i;
    }
  }
  return -1;
}


void parseSingleCommand(char* command, char* parsed_command[]){
#ifdef DEBUG
  printf("DEBUG: Parsing single command: %s\n", command);
#endif
  char* token;
  int i = 0;
  token = strtok(command, " ");
  while(token != NULL){
#ifdef DEBUG
    printf("DEBUG: token: %s\n", token);
#endif
    parsed_command[i] = token;
    token = strtok(NULL, " ");
    i++;
  }
  parsed_command[i] = NULL;


#ifdef DEBUG
  printf("DEBUG: Parsed command: [");
  int j = 0;
  while(parsed_command[j] != NULL){
    printf("%s, ", parsed_command[j]);
    j++;
  }
  printf("]\n");
#endif
}


void parseCommand(char* command, char* parsed_commands[][MAX_ARGS], int* has_pipe, char* pipe_pointers[2]){
#ifdef DEBUG
  printf("DEBUG: Parsing command: %s\n", command);
#endif
  int pipe_index = pipeIndex(command);
  if (-1 != pipe_index){
    *has_pipe = TRUE;
    char* parse1 = strdup(command);
    char* parse2 = strdup(command);
    pipe_pointers[0] = parse1;
    pipe_pointers[1] = parse2;
    parse1[pipe_index] = '\0';
    parse2 += pipe_index + 1;
    parseSingleCommand(parse1, parsed_commands[0]);
    parseSingleCommand(parse2, parsed_commands[1]);
  }
  else{
    parseSingleCommand(command, parsed_commands[0]);
  }
#ifdef DEBUG
  printf("\n");
  int i, max;
  max = pipe_index != -1 ? 2 : 1;
  for (i = 0; i < max; i++){
    printf("DEBUG: Parsed command %d:[", i);
    int j = 0;
    while(parsed_commands[i][j] != NULL){
      printf("%s, ", parsed_commands[i][j]);
      j++;
    }
    printf("]\n");
  }
#endif
}


char* getPath(const char* command){
  // Check if command exists in the local directory
  struct stat buf;
  if(lstat(command, &buf) == 0){
    char* absolute_path = realpath(command, NULL);
    if(absolute_path == NULL){
      fprintf(stderr, "ERROR: realpath failed");
      exit(EXIT_FAILURE);
    }
    return absolute_path;
  }

  char* path_env = getenv("MYPATH");
  if (path_env == NULL){
    path_env = "/bin:.";
  }

  char* path = strdup(path_env);
  char* token = strtok(path, ":");
  while(token != NULL){
    char* full_path = calloc(strlen(token) + strlen(command) + 2, sizeof(char));
    strcat(full_path, token);
    strcat(full_path, "/");
    strcat(full_path, command);
#ifdef DEBUG
    printf("DEBUG: full_path: %s\n", full_path);
#endif
    if(lstat(full_path, &buf) == 0){
      free(path);
      return full_path;
    }
    free(full_path);
    token = strtok(NULL, ":");
  }
  free(path);
  return NULL;
}


int executePipedCommands(char* parsed_commands[][MAX_ARGS], char* pipe_pointers[2]){
  int pipefd[2];
  int rc = pipe(pipefd);
  if(rc == -1){
    printf("rc=%d", rc);
    fprintf(stderr, "ERROR: pipe");
    free(pipe_pointers[0]);
    free(pipe_pointers[1]);
    exit(EXIT_FAILURE);
  }


  // ------------------------------------------------
  // FIRST COMMAND
  // ------------------------------------------------


  char* path = getPath(parsed_commands[0][0]);
  if(path == NULL){
    fprintf(stderr, "ERROR: command \"%s\" not found\n", parsed_commands[0][0]);
    free(path);
    free(pipe_pointers[0]);
    free(pipe_pointers[1]);
    return FAILURE;
  }
  
  //parsed_commands[0][0] = path;

  pid_t pid = fork();
  if (pid == -1){
    fprintf(stderr, "ERROR: fork failed");
    free(path);
    free(pipe_pointers[0]);
    free(pipe_pointers[1]);
    exit(EXIT_FAILURE);
  }
  else if (pid == 0){
#ifdef DEBUG
    printf("DEBUG: Child1 Executing %s\n", path);
#endif
    // Duplicating STDOUT to the write end of the pipe
    close(pipefd[0]);
    if (dup2(pipefd[1], STDOUT_FILENO) == -1){
      fprintf(stderr, "ERROR: dup2 failed");
      free(path);
      free(pipe_pointers[0]);
      free(pipe_pointers[1]);
      exit(EXIT_FAILURE);
    }
    close(pipefd[1]);
    
    if(execv(path, parsed_commands[0]) == -1){
      fprintf(stderr, "ERROR: execv failed");
      free(path);
      free(pipe_pointers[0]);
      free(pipe_pointers[1]);
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS); // Should never get here since execv replaces process
  }
  free(path);
  // ------------------------------------------------
  // SECOND COMMAND
  // ------------------------------------------------


  path = getPath(parsed_commands[1][0]);
  if (path == NULL) {
    fprintf(stderr, "ERROR: command \"%s\" not found\n", parsed_commands[0][0]);
    free(path);
    free(pipe_pointers[0]);
    free(pipe_pointers[1]);
    return FAILURE;
  }
  
  //parsed_commands[1][0] = path;

  pid_t pid2 = fork();
  if (pid2 == -1){  
    fprintf(stderr, "ERROR: fork failed");
    free(path);
    free(pipe_pointers[0]);
    free(pipe_pointers[1]);
    exit(EXIT_FAILURE);
  }
  else if (pid2 == 0){
#ifdef DEBUG
    printf("DEBUG: Child1 Executing %s\n", path);
#endif
    
    // Duplicating STDIN to the read end of the pipe
    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1){
      fprintf(stderr, "ERROR: dup2 failed");
      free(path);
      free(pipe_pointers[0]);
      free(pipe_pointers[1]);
      exit(EXIT_FAILURE);
    }
    close(pipefd[0]);
    
    if(execv(path, parsed_commands[1]) == -1){
      fprintf(stderr, "ERROR: execv failed");
      free(path);
      free(pipe_pointers[0]);
      free(pipe_pointers[1]);
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS); // Should never get here since execv replaces process
  }

  close(pipefd[0]);
  close(pipefd[1]);
  waitpid(pid, NULL, 0);
  waitpid(pid2, NULL, 0);
  free(path);
  free(pipe_pointers[0]);
  free(pipe_pointers[1]);
#ifdef DEBUG
  printf("DEBUG: Parent Finished\n");
#endif
  return SUCCESS;
}


int executeSingleCommand(char* args[]){
  //   Check for special commands (cd and exit)
  if (strcmp(args[0], "exit") == 0){
    return -1;
  }
  else if (strcmp(args[0], "cd") == 0){
    if (args[1] == NULL){
      if(chdir(getenv("HOME")) != 0){
        fprintf(stderr, "chdir() failed: Not a directory\n");
      }
      return SUCCESS;
    }
    else{
      if(chdir(args[1]) != 0){
        fprintf(stderr, "chdir() failed: Not a directory\n");
      }
      return SUCCESS;
    }
  }
  
#ifdef DEBUG
  printf("DEBUG: executeSingleCommand() Executing: %s\n", args[0]);  
#endif

  char* path = getPath(args[0]);
  if (path == NULL)
  {
    fprintf(stderr, "ERROR: command \"%s\" not found\n", args[0]);
    free(path);
    return FAILURE;
  }
  char* command = strdup(args[0]);
  
  //args[0] = path;

  // Else execute the command
  int len = arrayLength(args);
#ifdef DEBUG
  printf("len: %d\n", len);
  printf("path: %s\n", path);
#endif

  int foreground;
  if (len == 1){
    foreground = TRUE;
  }
  else{
#ifdef DEBUG
    printf("DEBUG: args[len - 1]: %s\n", args[len - 1]);
#endif
    foreground = (strcmp(args[len - 1], "&") == 0) ? FALSE : TRUE;
    if (foreground == FALSE){
      args[--len] = NULL;
    }
  }

  int pid;
  int status;
  pid = fork();
  if (pid < 0)
  {
    // Fork failed
    free(command);
    fprintf(stderr, "Fork failed\n");
    free(path);
    exit(EXIT_FAILURE);
  }
  else if (pid == 0)
  {
    if (execv(path, args) < 0)
    {
      free(command);
      free(path);
      return EXIT_FAILURE;
    }
  }
  else if (foreground == TRUE)
  {
    waitpid(pid, &status, 0);
  }
  else if (foreground == FALSE)
  {
    printf("[running background process \"%s\"]\n", command);
#ifdef DEBUG
    printf("[process %d]\n", pid);
#endif
    free(command);
    free(path);

    return pid;
  }
  free(command);
  free(path);
  return SUCCESS;
}


int main(){
  setvbuf(stdout, NULL, _IONBF, 0);
  char *command = (char *)malloc(MAX_CMD);
  char *parsed_commands[2][MAX_ARGS];
  pid_t *background_pids = (pid_t*)malloc(MAX_BGP * sizeof(pid_t));
  char *pipe_pointers[2];
  int background_pids_len = 0;
  printWorkingDirectory();

  while(TRUE){

    // Check for background processes that are finished
    for (int i = 0; i < background_pids_len; i++) {
#ifdef DEBUG
      printf("DEBUG: Checking background process %d\n", background_pids[i]);
#endif
      int status = 0;
      if (background_pids[i] == -1)
      {
        continue;
      }
      pid_t pid = waitpid(background_pids[i], &status, WNOHANG);
      if (pid > 0) {
        printf("[process %d terminated with exit status %d]\n", pid, status);
        background_pids[i] = -1;
      }
      if (WIFSIGNALED(status)) {
        printf("[process %d exited abnormally]", pid);
      }
    }

    // Read the command
    free(command);
    command = (char*)malloc(MAX_CMD);
    fgets(command, MAX_CMD, stdin);

#ifdef DEBUG
    printf("\nDEBUG: Command = %s\n", command);
#endif
    command[strlen(command) - 1] = '\0';
    
    // Parse the command
    int has_pipe = FALSE;
    parseCommand(command, parsed_commands, &has_pipe, pipe_pointers);
    if (parsed_commands[0][0] == NULL){
      continue;
    }

    if (has_pipe == TRUE){
      executePipedCommands(parsed_commands, pipe_pointers);
    }
    else{
      int status = executeSingleCommand(parsed_commands[0]);
#ifdef DEBUG
      printf("DEBUG: status: %d\n", status);
#endif
      if (status < 0){
        goto exit_shell;
      }
      else if (status > 1) {
        background_pids[background_pids_len] = status;
        background_pids_len++;
      }
    }

    usleep(10);
    printWorkingDirectory();
  }

exit_shell:
  free(command);
  free(background_pids);
  printf("bye\n");
}

