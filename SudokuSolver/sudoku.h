/* Header file "Sudoku.h" */

#ifndef SUDOKU_H
#define SUDOKU_H

const int N = 9; //Row of matrix
const int M = 9; //Column of matrix

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[N][M]);

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[N][M]);

/* Function to determine if the board is complete and it returns a boolean */
bool is_complete(char board[N][M]);

/* Function to check if putting a digit in a particular position is valid and it returns a boolean */
bool make_move(char position[], char digit, char board[N][M]);

/* Function to check if the coordinates are out of range and it returns a boolean */
bool check_out_of_range(char position[]);

/* Function to check if there is a same digit in the row and it returns a boolean */
bool row_check(char position[], char digit, char board[N][M]);

/* Function to check if there is a same digit in the column and it returns a boolean */
bool column_check(char position[], char digit, char board[N][M]);

/* Function to check if there is a same digit in the box and it returns a boolean */
bool box_check(char position[], char digit, char board[N][M]);

/* Function to save the board in a file with different name and it returns a boolean */
bool save_board(const char* filename, char board[N][M]);

/* Function to find empty cells in the board, its location will be stored and it returns a boolean */
bool find_empty_cell(int& row, int& column, char board[N][M]);

/* Function to find the solution to sudoku using the recursion method and it returns a boolean */
bool solve_board(char board[N][M]);

/* Overloading function of solve_board that counts function calls */
bool solve_board(char board[N][M], int& count);

#endif
