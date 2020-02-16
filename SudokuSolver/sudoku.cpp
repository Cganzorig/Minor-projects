/* Implementation file "Sudoku.cpp" */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;



/* Function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}
/* End function */

/* Helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* Helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}
/* End function */

/* Function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}
/* End function */

/* Function to determine if the board is complete and it returns a boolean */
bool is_complete(char board[N][M])
{
  for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
	  if (board[i][j] == '.') //Iterates through every position to check whether there are empty cells or not
	    return false;
	}
  }

  return true;
};
/* End function */

/* Function to check if putting a digit in a particular position is valid and it returns a boolean */
bool make_move(char position[], char digit, char board[N][M])
{
  int row, column;

  //Converting characters into integers
  row = position[0] - 65;
  column = atoi(position+1) - 1;

  //Storing the address of a variable at the particular position using a pointer
  char* ptr = &board[row][column];

  //Checking if putting a digit in the particulars satisfies all the conditions 
  if(check_out_of_range(position) == false || row_check(position, digit, board) == false || column_check(position, digit, board) == false || box_check(position, digit, board) == false) {
      return false;
    } else {
      *ptr = digit; //Changing the value using the pointer if it satisfies all the condition
      return true;
    }
    
};
/* End function */

/* Function to check if the coordinates are out of range and it returns a boolean */
bool check_out_of_range(char position[])
{
  if (position[0] < 'A' || position[0] > 'I' || position[1] < '1' || position[1] > '9')
      return false;
  else
    return true;
}
/* End function */

/* Function to check if there is a same digit in the row and it returns a boolean */
bool row_check(char position[], char digit, char board[N][M])
{
  int row;

  //Converting the character into integer
  row = position[0] - 65;
  
  //Looping through the row to find if there is a similar number in the row
  for (int i = 0; i < N; i++) {
      if (board[row][i] == digit)
	return false;
    }
  return true;
};
/* End function */

/* Function to check if there is a same digit in the column and it returns a boolean */
bool column_check(char position[], char digit, char board[N][M])
{
  int column;

  //Converting the character into integer
  column = atoi(position+1) - 1;

  //Looping through the row to find if there is a similar number in the row
  for (int i = 0; i < 9; i++) {
      if(board[i][column] == digit)
	return false;
    }
    return true;
};
/* End function */

/* Function to check if there is a same digit in the box and it returns a boolean */
bool box_check(char position[], char digit, char board[N][M])
{
  int row, column;

  //Converting the character into integer
  row = position[0] - 65;
  column = atoi(position+1)-1;

  int k, l;

  //Finding the first position of the row in the particular box to loop through all the position in the box
  if (row >= 0 && row <= 2)
    k = 0;
  else if (row >= 3 && row <= 5)
      k = 3;
  else if (row >= 6 && row <= 8)
      k = 6;

  //Finding the first position of the column in the particular box to loop through all the position in the box
  if (column >= 0 && column <= 2)
    l = 0;
  else if(column >= 3 && column <= 5)
    l = 3;
  else if(column >= 6 && column <= 8)
    l = 6;     

  //Looping through all the position in the box to check if there is a similar number in the box
  for (int i = k; i < (k+3); i++) {
    for (int j = l; j < (l+3); j++) {
	if(board[i][j] == digit)
	  return false;
      }
  }
  return true;
};
/* End function */

/* Function to save the board in a new file and it returns a boolean */
bool save_board(const char* filename,char board[N][M])
{
  ofstream out_stream;
  
  out_stream.open(filename);

  for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
	  //Putting every character of the board into the file
	  out_stream.put(board[i][j]); 
	}
      //Putting new line
      out_stream.put('\n'); 
    }
  
  out_stream.close();

  //Checking if the file was successfully created 
  if(!out_stream.fail())
    return true;
  else
    return false;
};
/* End function */

/* Function to find empty cells in the board, its location will be stored and it returns a boolean */
bool find_empty_cell(int& row, int& column, char board[N][M])
{
  for (row = 0; row < N; row++) {
      for (column = 0; column < M; column++) {
	  if (board[row][column] == '.')
	    return true;
	}
    }
  return false;
};
/* End function */

/* Function to find the solution to sudoku using the recursion method and it returns a boolean */
bool solve_board(char board[N][M])
{
  char position[2];
  int row, column;

  //Base case
  if(is_complete(board)) 
    return true;

  //Finding the next empty cell
  if(!find_empty_cell(row, column, board)) 
    return true;

  position[0] = row + 65;
  position[1] = column + 49;

  //Looping through integers 1-9 to find a valid integer at the particular position
  for (char num = '1'; num < '1' + 9; num++) {
    
      //If-condition to check if putting a digit into a particular position is a valid move
      if(make_move(position, num, board)) {
	
	  //Calling the function again to find a valid integer at the next position in the box
	  if(solve_board(board)) 
	    return true; //If the function reaches to the base case, it returns true
	  
	  //In case of failure, it leaves empty
	  board[row][column] = '.';
	}
    }
  //If there is no solution, it returns false
  return false; 
};
/* End function */

/* Overleading function of solve_board that counts function calls */
bool solve_board(char board[N][M], int& count)
{
  count++;
  
  char position[2];
  int row, column;

  //Base case
  if(is_complete(board)) 
    return true;

  //Finding the next empty cell
  if(!find_empty_cell(row, column, board)) 
    return true;

  position[0] = row + 65;
  position[1] = column + 49;

  //Looping through integers 1-9 to find a valid integer at the particular position
  for (char num = '1'; num < '1' + 9; num++) {
    
      //If condition to check if putting a digit into a particular position is valid
      if(make_move(position, num, board)) {

	//Calling the function again to find a valid integer at the next position in the box	
	  if(solve_board(board, count)) 
	    return true; //If the function reaches base case, it returns true
	  
	  //In case of failure, it leaves empty
	  board[row][column] = '.';
	}
    }
  //If there is no solution, it returns false
  return false; 
};
/* End function */
