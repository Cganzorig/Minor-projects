#include "Piece.h"

Piece::Piece(Colour colour, string initial_position): colour(colour), initial_position(initial_position){};

Piece::~Piece(){};

Colour Piece::get_colour() {
  return colour;
};

string Piece::get_initial_position() {
  return initial_position;
};

string Piece::get_previous_position() {
  return previous_position;
};

void Piece::set_initial_position(string temp_position) {
  initial_position = temp_position;
};

void Piece::set_previous_position(string temp_position) {
  previous_position = temp_position;
};

bool Piece::check_same_rank(string first_position, string second_position) {
  if(first_position[1] == second_position[1])
    return true;
  else
    return false;
};

bool Piece::check_same_file(string first_position, string second_position) {
  if(first_position[0] == second_position[0])
    return true;
  else
    return false;
};

bool Piece::check_same_diagonal(string first_position, string second_position) {
  if(abs(second_position[0] - first_position[0]) == abs(second_position[1] - first_position[1]))
    return true;
  else
    return false;
};

bool Piece::check_clear_rank(string first_position, string second_position, map<string, Piece*> Board) {
  if(!check_same_rank(first_position, second_position))
    return false;
  
  string position = second_position;
  int x_increase;
  
  if(first_position[0] > second_position[0])
    x_increase = 1;
  else
    x_increase = -1;
  
  while((position[0] += x_increase) != first_position[0]) {
    if(Board[position] != nullptr )
      return false;
  }
  return true;
};

bool Piece::check_clear_file(string first_position, string second_position, map<string, Piece*> Board) {
  if(!check_same_file(first_position, second_position))
    return false;
  
  string position = second_position;
  int y_increase;
  
  if(first_position[1] > second_position[1])
    y_increase = 1;
  else
    y_increase = -1;
  
  while((position[1] += y_increase) != first_position[1]) {
    if(Board[position] != nullptr )
      return false;
  }
  return true;
};

bool Piece::check_clear_diagonal(string first_position, string second_position, map<string, Piece*> Board) {
  if(!check_same_diagonal(first_position, second_position))
    return false;
  
  string position = second_position;
  int x_increase, y_increase;
  
  if(first_position[0] > second_position[0] && first_position[1] > second_position[1]) {
    x_increase = 1;
    y_increase = 1;
  } else if(first_position[0] > second_position[0] && first_position[1] < second_position[1]) {
    x_increase = 1;
    y_increase = -1;
  } else if(first_position[0] < second_position[0] && first_position[1] > second_position[1]) {
    x_increase = -1;
    y_increase = 1;
  } else {
    x_increase = -1;
    y_increase = -1;
  }

  while((position[0] += x_increase) != first_position[0]) {
    position[1] += y_increase;
    if(Board[position] != nullptr )
      return false;
  }
  return true;
};


