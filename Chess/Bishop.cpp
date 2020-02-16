#include "Bishop.h"

Bishop::Bishop(Colour colour, string initial_position): Piece(colour, initial_position) {
  if(colour == Colour::White)
    symbol = "♝";
  else
    symbol = "♗";
};

Bishop::~Bishop(){};

bool Bishop::check_validation(string next_position, map<string, Piece*> Board, int& error) {
  if(check_clear_diagonal(initial_position, next_position, Board)) {
    return true;
  } else {
    error = ERROR_INVALID_BISHOP_MOVE;
    return false;
  }
};
