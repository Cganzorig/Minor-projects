#include "Knight.h"


Knight::Knight(Colour colour, string initial_position): Piece(colour, initial_position) {
  if(colour == Colour::White)
    symbol = "♞";
  else
    symbol = "♘";
};

Knight::~Knight(){};

bool Knight::check_validation(string next_position, map<string, Piece*> Board, int& error) {
  if((abs(next_position[0] - initial_position[0]) == 2 &&
      abs(next_position[1] - initial_position[1]) == 1) ||
     (abs(next_position[1] - initial_position[1]) == 2 &&
      abs(next_position[0] - initial_position[0]) == 1)) {
    return true;
  } else {
    error = ERROR_INVALID_KNIGHT_MOVE;
    return false;
  }
};
