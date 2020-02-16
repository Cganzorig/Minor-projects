#include "Queen.h"

Queen::Queen(Colour colour, string initial_position): Piece(colour, initial_position) {
  if(colour == Colour::White)
    symbol = "♛";
  else
    symbol = "♕";
};

Queen::~Queen(){};

bool Queen::check_validation(string next_position, map<string, Piece*> Board, int& error) {
  if(check_clear_rank(initial_position, next_position, Board) ||
     check_clear_file(initial_position, next_position, Board) ||
     check_clear_diagonal(initial_position, next_position, Board)) {
    return true;
  } else {
    error = ERROR_INVALID_QUEEN_MOVE;
    return false;
  }
};
