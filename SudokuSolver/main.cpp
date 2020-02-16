/* THIS PROGRAM SOLVES SUDOKU PUZZLES */

#include <iostream>
#include <cstdio>
#include <fstream>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];
  
  /* This section illustrates the use of the pre-supplied helper functions. */
  
  cout << "============= Pre-supplied functions =============" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "=================== Question 1 ===================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "=================== Question 2 ===================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

  //Test for checking if the coordinates are out of range
  cout << "Putting '6' into K10 is ";
  if (!make_move("K10", '6', board)) 
   cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  
  //Test for checking if there is a same digit in the row
  cout << "Putting '3' into A2 is ";
  if (!make_move("A2", '3', board)) 
   cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  
  //Test for checking if there is a same digit in the column
  cout << "Putting '6' into A2 is ";
  if (!make_move("A2", '6', board)) 
   cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  
  //Test for checking if there is a same digit in the box
  cout << "Putting '4' into A1 is ";
  if (!make_move("A1", '4', board)) 
   cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  
  cout << "=================== Question 3 ===================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "=================== Question 4 ===================" << endl << endl;

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  cout << "=================== Question 5 ===================" << endl << endl;

  int number_of_function_calls_1 = 0;

  load_board("mystery1.dat", board);
  if (solve_board(board, number_of_function_calls_1)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
    cout << "Number of recursive function calls: " << number_of_function_calls_1 << endl;
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  
  int number_of_function_calls_3 = 0;

  load_board("mystery3.dat", board);
  if (solve_board(board, number_of_function_calls_3)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
    cout << "Number of recursive function calls: " << number_of_function_calls_3 << endl;
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
 
  return 0;
}
