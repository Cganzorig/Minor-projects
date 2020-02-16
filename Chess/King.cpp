#include "King.h"

King::King(Colour colour, string initial_position): Piece(colour, initial_position) {
  initial_move = true;
  if(colour == Colour::White)
    symbol = "♚";
  else
    symbol = "♔";
};

King::~King(){};

bool King::get_move() {
  return initial_move;
};

void King::set_move(bool temp) {
  initial_move = false;
};

bool King::check_validation(string next_position, map<string, Piece*> Board, int& error) {
  if((abs(next_position[0] - initial_position[0]) == 1 &&
      abs(next_position[1] - initial_position[1]) <= 1) ||
     (abs(next_position[0] - initial_position[0]) == 0 &&
      abs(next_position[1] - initial_position[1]) <= 1)) {
    return true;
  } else {
    error = ERROR_INVALID_KING_MOVE;
    return false;
  }
};



