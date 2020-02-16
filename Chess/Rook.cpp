#include "Rook.h"

Rook::Rook(Colour colour, string initial_position): Piece(colour, initial_position) {
  initial_move = true;
  if(colour == Colour::White)
    symbol = "♜";
  else
    symbol = "♖";
};

Rook::~Rook(){};

bool Rook::get_move() {
  return initial_move;
};

void Rook::set_move(bool value) {
  initial_move = false;
};

bool Rook::check_validation(string next_position, map<string, Piece*> Board, int& error) {
  if(check_clear_rank(initial_position, next_position, Board) ||
     check_clear_file(initial_position, next_position, Board)) {
    return true;
  } else {
    error = ERROR_INVALID_ROOK_MOVE;
    return false;
  }
};

