#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdint.h>

#ifdef DEBUG
#define DEBUG_STR "DEBUG: "
#endif
#ifndef DEBUG
#define DEBUG_STR ""
#endif


// ---------------------- FUNCTION PROTOTYPES ----------------------


int** copy_board(int** board);
void free_board(int** board);
int*** make_state(int** board, int x, int y, int* move_number);


// ---------------------- GLOBAL VARIABLES ----------------------


int n, m;
int max_tour_length = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int y_moves[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int x_moves[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int min_deadend_size = 0;
int ***dead_end_boards;
int dead_end_board_count = 0;
int dead_end_boards_size = 1;


// ----------------- CODE FOR THE KNIGHT'S TOUR -----------------


// Parses command line arguments and sets global variables n, m, min_deadend_size
int parse_arguments(int argc, char *argv[])
{
    // Parse arguments
    if (argc != 3 && argc != 4)
    {
        printf("%sUsage: ./hw03 <board dim n> <board dim m> <OPTIONAL min deadend size>\n", DEBUG_STR);
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    if (n <= 0 || m <= 0)
    {
        printf("%sBoard dimensions must be positive integers\n", DEBUG_STR);
        return EXIT_FAILURE;
    }
    if (argc == 4)
    {
        min_deadend_size = atoi(argv[3]);
        if (min_deadend_size < 0)
        {
            printf("%sMinimum deadend size must be a non-negative integer\n", DEBUG_STR);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}


// Stores a dead end board in the global dead_end_boards array, expands global array if needed
void copystore_deadend_board(int** board)
{
#ifdef DEBUG
    printf("DEBUG: THREAD %ld: Storing dead end board\n", (long)pthread_self());
    printf("DEBUG: THREAD %ld: Dead end board count: %d\n", (long)pthread_self(), dead_end_board_count);
#endif
    pthread_mutex_lock(&mutex);

    // Double the capacity aeach time we run out of space
    if (dead_end_board_count == dead_end_boards_size)
    {   
#ifdef DEBUG
        printf("DEBUG: THREAD %ld: Doubling dead end board capacity from %d to %d\n", (long)pthread_self(), dead_end_boards_size, 2*dead_end_boards_size);
#endif
        dead_end_boards_size *= 2; 
        dead_end_boards = (int***)realloc(dead_end_boards, dead_end_boards_size * sizeof(int **));
    }
#ifdef DEBUG
    printf("DEBUG: THREAD %ld: Dead end board allocated: %d\n", (long)pthread_self(), dead_end_board_count);
#endif


    // Allocate space for current board
    dead_end_boards[dead_end_board_count] = copy_board(board);
    dead_end_board_count++;
#ifdef DEBUG
    printf("DEBUG: THREAD %ld: Dead end board count after storing: %d\n", (long)pthread_self(), dead_end_board_count);
#endif

    pthread_mutex_unlock(&mutex);
}


// Checks if a position is valid on the board
bool is_valid_position(int x, int y, int **board)
{
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] == 0;
}


// returns a deep copy of a board
int** copy_board(int** board){
    int** new_board = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++){
        new_board[i] = (int*)calloc(m, sizeof(int));
        for (int j = 0; j < m; j++){
            new_board[i][j] = board[i][j];
        }
    }
    return new_board;
}


// Frees a board
void free_board(int** board){
    for (int i = 0; i < n; i++){
        free(board[i]);
    }
    free(board);
} 


// Packs a board and position into a newly allocated state
int*** make_state(int** board, int x, int y, int* move_number){
    //Create a new state with a copy of board and new position
    int*** state = (int***)calloc(2, sizeof(int**));
    state[0] = copy_board(board);
    state[1] = (int**)calloc(1, sizeof(int*));
    ((int*)state[1])[0] = x;
    ((int*)state[1])[1] = y;
    ((int*)state[1])[2] = *move_number;
    return state;
}


// Prints a board
void print_board(int **board)
{
    for (int i = 0; i < n; i++)
    {
        printf("%sTHREAD %ld: ", DEBUG_STR, (long)pthread_self());
        for (int j = 0; j < m; j++)
        {
#ifdef DEBUG
            printf("%d", board[i][j]);
#endif
#ifndef DEBUG
            printf("%c", (board[i][j] != 0) ? 'S' : '.');
#endif
        }
        printf("\n");
    }
}


// Recursive function to find a knight's tour from a given state
void* knight_tour_from_state(void* state)
{   
    // Unpack board, position from state
    int **board = ((int***)state)[0];
    int *position = (int*)((int***)state)[1];
    int curr_x = position[0];
    int curr_y = position[1];
    int move_number = position[2];

    free(position);
    free(state);

#ifdef DEBUG
    printf("DEBUG: THREAD %ld: Starting from position (%d, %d) with move number %d\n", (long)pthread_self(), curr_x, curr_y, move_number);
#endif

    // Check if position is valid, should never really be invalid here
    if (!is_valid_position(curr_x, curr_y, board))
    {
#ifdef DEBUG
        printf("DEBUG: THREAD %ld: Invalid position (%d, %d). Exiting...\n", (long)pthread_self(), curr_x, curr_y);
#endif
        free_board(board);
        pthread_exit(NULL);
    }

    // Update square as visited
    board[curr_x][curr_y] = move_number;

#ifdef DEBUG
    printf("DEBUG: THREAD %ld: Updated board after move #%d\n", (long)pthread_self(), move_number);
    print_board(board);
#endif

    // If all squares visited, valid tour found
    if (move_number == n * m )
    {
        printf("%sTHREAD %ld: Sonny found a full knight's tour!\n", DEBUG_STR, (long)pthread_self());
        pthread_mutex_lock(&mutex);
        max_tour_length = (move_number > max_tour_length) ? move_number : max_tour_length;
        pthread_mutex_unlock(&mutex);
#ifdef DEBUG
        printf("DEBUG: THEAD %ld: perfect tour, exiting...", (long)pthread_self());
#endif
        free_board(board);
        pthread_exit((void*)(intptr_t)move_number);
    }

    // Find all valid moves
    int valid_move_count = 0;
    int valid_x, valid_y; // For single valid move 
    for (int i = 0; i < 8; i++)
    {
        int new_x = curr_x + x_moves[i];
        int new_y = curr_y + y_moves[i];

        if (is_valid_position(new_x, new_y, board))
        {
            valid_move_count++;
            valid_x = new_x;
            valid_y = new_y;
#ifdef DEBUG
            printf("DEBUG: THREAD %ld: Valid move: (%d, %d) from (%d, %d)\n", (long)pthread_self(), valid_x, valid_y, curr_x, curr_y);
#endif

        }
    }

#ifdef DEBUG
    printf("DEBUG: THREAD %ld: Valid moves from current position: %d\n", (long)pthread_self(), valid_move_count);
#endif

    // If no valid moves, deadend
    if (valid_move_count == 0)
    {
        copystore_deadend_board(board);
#ifdef DEBUG
        printf("DEBUG: THREAD %ld: Dead end board stored\n", (long)pthread_self());
#endif

        free_board(board);
        pthread_mutex_lock(&mutex);
#ifdef DEBUG
        printf("DEBUG: THREAD %ld: dead end  move_number = %d, max_tour_length = %d \n", (long)pthread_self(), move_number, max_tour_length);
        if (move_number > max_tour_length)
            printf("DEBUG: THREAD %ld: dead end max_tour_length updated from %d to %d\n", (long)pthread_self(), max_tour_length, move_number);
#endif
        max_tour_length = (move_number > max_tour_length) ? move_number : max_tour_length;
        
        pthread_mutex_unlock(&mutex);
        pthread_exit((void*)(intptr_t)move_number);
    }

    // One valid move, do not make thread
    // However, we need to correctly get move number from the recursive call
    if (valid_move_count == 1)
    {   
        move_number++;
        int ***next_state = make_state(board, valid_x, valid_y, &move_number);
        knight_tour_from_state(next_state);
        free_board(board);
        pthread_exit((void*)(intptr_t)move_number);
    }

    // More than 1 valid move, make a new thread for each move
    printf("%sTHREAD %ld: %d moves possible after move #%d; creating threads...\n", DEBUG_STR, (long)pthread_self(), valid_move_count, move_number);
    pthread_t *threads = (pthread_t *)malloc(valid_move_count * sizeof(pthread_t));
    int new_move_numbers[valid_move_count];
    int thread_index = 0;
    for (int i = 0; i < 8; i++)
    {

        int new_x = curr_x + x_moves[i];
        int new_y = curr_y + y_moves[i];

        if (!is_valid_position(new_x, new_y, board))
        {
            continue;
        }

#ifdef DEBUG
        printf("DEBUG: THREAD %ld: Trying to move to (%d, %d)\n", (long)pthread_self(), new_x, new_y);
#endif
        new_move_numbers[thread_index] = move_number + 1;
        int ***next_state = make_state(board, new_x, new_y, &new_move_numbers[thread_index]);
        pthread_create(&threads[thread_index], NULL, knight_tour_from_state, next_state);
        int joined_move_number;
        pthread_join(threads[thread_index], (void **)&joined_move_number);
        printf("%sTHREAD %ld: Thread [%ld] joined from single (returned %d)\n", DEBUG_STR, (long)pthread_self(), (long)threads[thread_index], joined_move_number);
        thread_index++;
    }

#ifdef DEBUG
    printf("DEBUG: THREAD %ld: Created %d threads\n", (long)pthread_self(), valid_move_count);
    for(int i = 0; i < valid_move_count; i++)
    {
        printf("DEBUG: THREAD %ld: Thread [%ld] created\n", (long)pthread_self(), (long)threads[i]);
    }
#endif
    // Backtrack and free memory
    free_board(board);
    free(threads);
    pthread_exit((void*)(intptr_t)(move_number + 1));
}


int main(int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IONBF, 0);

    if (parse_arguments(argc, argv) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

#ifdef DEBUG
    printf("DEBUG: Board dimensions: %d x %d\n", n, m);
    printf("DEBUG: Minimum deadend size: %d\n", min_deadend_size);
#endif

    // Initialize board and dead end boards (will be dynamically allocated as needed)
    int** board = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        board[i] = calloc(m, sizeof(int));
    }

    int** test_copy_board = copy_board(board);
    free_board(test_copy_board);
    dead_end_boards = (int ***)malloc(1 * sizeof(int **));

    printf("%sTHREAD %ld: Solving Sonny's knight's tour problem for a %dx%d board\n", DEBUG_STR, (long)pthread_self(), n, m);

    // Each state has form [board = int[int[]]], position = int[3]].
    // Note position casts int** to int* for easy indexing
    int* start_move_number = calloc(1, sizeof(int));
    start_move_number[0] = 1;
    int ***start_state = make_state(board, 0, 0, start_move_number);
    pthread_t root_thread;
    pthread_create(&root_thread, NULL, knight_tour_from_state, start_state);
    int joined_move_number;
    pthread_join(root_thread, (void**)&joined_move_number);
    printf("%sTHREAD %ld: Starter Thread [%ld] joined (returned %d)\n", DEBUG_STR, (long)pthread_self(), (long)root_thread, joined_move_number);
    // Print best solution
    printf("%sTHREAD %ld: Best solution found visits %d squares (out of %d)\n", DEBUG_STR, (long)pthread_self(), max_tour_length, n * m);
    // Print dead end boards
    printf("%sTHREAD %ld: Dead end boards:\n", DEBUG_STR, (long)pthread_self());
    for (int i = 0; i < dead_end_board_count; i++)
    {
        printf("%sTHREAD %ld: Dead end board #%d:\n", DEBUG_STR, (long)pthread_self(), i);
        print_board(dead_end_boards[i]);
    }

    // Clean up
    return EXIT_SUCCESS;
}