#include "Pawn.h"


Pawn::Pawn(Colour colour, string initial_position): Piece(colour, initial_position) {
  initial_move = true;
  if(colour == Colour::White)
    symbol = "♟";
  else
    symbol = "♙";
};

Pawn::~Pawn(){};

void Pawn::set_move(bool temp) {
  initial_move = false;
};

bool Pawn::check_two_steps_forward(string next_position, map<string, Piece*> Board, int sign) {
  string middle_position = next_position;
  middle_position[1] -= sign;
  if(initial_move && (next_position[0] == initial_position[0]) &&
     (next_position[1] == initial_position[1] + 2*sign) &&
     Board[middle_position] == nullptr && Board[next_position] == nullptr &&
     Board["" + next_position[0] + (next_position[1] - sign)] == nullptr) {
    return true;
  } else
    return false;
};

bool Pawn::check_one_step_forward(string next_position, map<string, Piece*> Board, int sign) {
  if(next_position[0] == initial_position[0] && (next_position[1] == initial_position[1] + 1*sign) &&
     Board[next_position] == nullptr) {
    return true;
  } else
    return false;
};

bool Pawn::check_capture(string next_position, map<string, Piece*> Board, int sign) {
  if((next_position[1] == (initial_position[1] + sign)) &&
     (next_position[0] == (initial_position[0] - 1) ||
      next_position[0] == (initial_position[0] + 1)) &&
     Board[next_position] != nullptr) {
    return true;
  } else
    return false;
};

bool Pawn::check_enpassant(string next_position, map<string, Piece*> Board, int sign) {
  string left_side = string(1, (initial_position[0] - sign)) + string(1, initial_position[1]);
  string right_field = string(1, (initial_position[0] + sign)) + string(1, initial_position[1]);

  //Enpassant condtion is met if there is a pawn of opposite player that is captured and next field of pawn that attacks is no empty
  if((Board.find(left_side) != Board.end()) &&
     Board[left_side] != nullptr &&
     (Board[left_side] == dynamic_cast<Pawn*>(Board[left_side])) &&
     (Board[left_side]->get_colour() != colour) &&
     ((Board[left_side]->get_previous_position())[0] == left_side[0]) &&
     ((Board[left_side]->get_previous_position())[1] == left_side[1] + 2*sign) &&
     (next_position[0] == initial_position[0] - sign) &&
     (next_position[1] == initial_position[1] + sign)) {
    return true;
  } else if((Board.find(right_field) != Board.end()) &&
	    Board[right_field] != nullptr &&
	    (Board[right_field] == dynamic_cast<Pawn*>(Board[right_field])) &&
	    (Board[right_field]->get_colour() != colour) &&
	    ((Board[right_field]->get_previous_position())[0] == right_field[0]) &&
	    ((Board[right_field]->get_previous_position())[1] == right_field[1] + 2*sign) &&
	    (next_position[0] == initial_position[0] + sign) &&
	    (next_position[1] == initial_position[1] + sign)) {
    return true;
  }
  return false;
};

bool Pawn::check_validation(string next_position, map<string, Piece*> Board, int& error) {
  int sign;
  
  if(get_colour() == Colour::White)
    sign = 1;
  else
    sign = -1;
  
  if(check_two_steps_forward(next_position, Board, sign) ||
     check_one_step_forward(next_position, Board, sign) ||
     check_capture(next_position, Board, sign) ||
     check_enpassant(next_position, Board, sign)) {
    return true;
  } else {
    error = ERROR_INVALID_PAWN_MOVE;
    return false;
  }
};
