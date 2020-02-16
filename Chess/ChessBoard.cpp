#include "ChessBoard.h"

ChessBoard::ChessBoard() {
  board_setup();
}

ChessBoard::~ChessBoard() {
  clean();
}

void ChessBoard::submitMove(string initial_position, string next_position) {
  int error = SUCCESS;
  
  initial_position[0] = toupper(initial_position[0]);
  next_position[0] = toupper(next_position[0]);
  
  if(game_on) {
    if(check_castling(initial_position, next_position, error)) {
      if(error == ERROR_PUTTING_OWN_KING_IN_CHECK ||
	 error == ERROR_CASTLING_IMPOSSIBLE) {
	print_error(initial_position, next_position, error);
	return;
      } else {
	print_board();
	switch_turn();
	return;
      }
    } else if(check_validation(initial_position, next_position, error)) {
      print_move(initial_position, next_position);
      if(!(initial_position.compare(white_king_position)))
	white_king_position = next_position;
      else if(!(initial_position.compare(black_king_position)))
	black_king_position = next_position;
      
      print_capture(next_position);

      //Check if promotion and enpassant condition are met if it is a pawn
      if(dynamic_cast<Pawn*>(Board[initial_position])) {
	check_promotion(initial_position, next_position, error); 
	check_enpassant(initial_position, next_position, error);
	if(error == ERROR_PUTTING_OWN_KING_IN_CHECK) {
	  print_error(initial_position, next_position, error);
	  return;
	}
      }

      //Setting initial moves of following pieces to false
      if(dynamic_cast<Pawn*>(Board[initial_position]))
	dynamic_cast<Pawn*>(Board[initial_position])->set_move(false);
      if(dynamic_cast<Rook*>(Board[initial_position]))
	dynamic_cast<Rook*>(Board[initial_position])->set_move(false);
      if(dynamic_cast<King*>(Board[initial_position]))
	dynamic_cast<King*>(Board[initial_position])->set_move(false);

      //Captured piece will be stored and it will be set back to previous position in case of need
      Piece* captured_piece = nullptr;
      if(Board[next_position] != nullptr) {
	captured_piece = Board[next_position];
	Board[next_position] = nullptr;
      }

      //Setting position of piece
      string previous_position = Board[initial_position]->get_previous_position();
      Board[initial_position]->set_previous_position(initial_position);
      Board[initial_position]->set_initial_position(next_position);
      Board[next_position] = nullptr;
      Board[next_position] = Board[initial_position];
      Board[initial_position] = nullptr;

      //Setting position of king to position of king of opposite player
      string opposite_king_position;
      string king_position = get_king_position();
      if(get_player_turn() == Colour::White)
	opposite_king_position = black_king_position;
      else
	opposite_king_position = white_king_position;

      if(dynamic_cast<King*>(Board[next_position]))
	king_position = next_position;

      //Checking if the move puts own king in check and it will bet set back to previous position if so
      if(check_own(king_position)) {
	Board[initial_position] = Board[next_position];
	Board[next_position] = captured_piece;
	error = ERROR_PUTTING_OWN_KING_IN_CHECK;
	print_error(initial_position, next_position, error);
	return;
      }
      
      delete captured_piece;
      
      if(check(opposite_king_position)) {
	vector<string> threatening_pieces;
	string attacking_piece;
	
	threatening_pieces = pieces_can_move_to_position(opposite_king_position);
	
	if (white_turn)
	  cout << "Black is in check" << endl;
	else
	  cout << "White is in check" << endl;

	attacking_piece = threatening_pieces[0];
	
	if(checkmate(opposite_king_position, attacking_piece)) {
	  cout << endl << "CHECKMATE! ";
	  
	  if(Board[attacking_piece]->get_colour() == Colour::White)
	    winner = Winner::White;
	  else
	    winner = Winner::Black;
	  
	  game_on = false;
	  print_result();
	  exit(SUCCESS);
	}
      }
      print_board();
      
      switch_turn();

      if(check_stalemate()) {
	winner = Winner::Draw;
	game_on = false;
	print_result();
	exit(SUCCESS);
      }
      
    } else {
      print_error(initial_position, next_position, error);
    }
  } else {
    error = ERROR_GAME_IS_OFF;
    print_error(initial_position, next_position, error);
  }
};

void ChessBoard::resetBoard() {
  clean();
  board_setup();
};

void ChessBoard::board_setup() {
  winner = Winner::Draw;
  white_turn = true;
  game_on = true;
  print_board_value = true;

  string position;

  Board["A1"] = new Rook(Colour::White, "A1");
  Board["B1"] = new Knight(Colour::White, "B1");
  Board["C1"] = new Bishop(Colour::White, "C1");
  Board["D1"] = new Queen(Colour::White, "D1");
  Board["E1"] = new King(Colour::White, "E1");
  Board["F1"] = new Bishop(Colour::White, "F1");
  Board["G1"] = new Knight(Colour::White, "G1");
  Board["H1"] = new Rook(Colour::White, "H1");

  for(position = "A2"; position[0] <= 'H'; position[0]++)
    Board[position] = new Pawn(Colour::White, position);
  
  Board["A8"] = new Rook(Colour::Black, "A8");
  Board["B8"] = new Knight(Colour::Black, "B8");
  Board["C8"] = new Bishop(Colour::Black, "C8");
  Board["D8"] = new Queen(Colour::Black, "D8");
  Board["E8"] = new King(Colour::Black, "E8");
  Board["F8"] = new Bishop(Colour::Black, "F8");
  Board["G8"] = new Knight(Colour::Black, "G8");
  Board["H8"] = new Rook(Colour::Black, "H8");

  for(position = "A7"; position[0] <= 'H'; position[0]++)
    Board[position] = new Pawn(Colour::Black, position);
  
  for(int rank = 3; rank <= 6; rank++) {
    for(char file = 'A'; file <= 'H'; file++)
      Board[string(1,file) + to_string(rank)] = nullptr;
  }
  
  white_king_position = "E1";
  black_king_position = "E8";

  cout << "A new chess game is started!" << endl;

  print_board();
};

void ChessBoard::clean() {
  map<string, Piece*>::iterator it;
  for(it = Board.begin(); it != Board.end(); ++it)
    delete it->second;
};

void ChessBoard::switch_turn() {
  white_turn = !white_turn;
};

vector<string> ChessBoard::pieces_can_move_to_position(string position) {
  int error;
  vector<string> pieces;
  map<string, Piece*>::iterator it;
  for(it = Board.begin(); it != Board.end(); ++it) {
    if((it->second) != nullptr &&
       (it->second)->get_colour() == get_player_turn() &&
       check_validation((it->first), position, error)) {
      pieces.push_back((it->first));
    }
  }
  return pieces;
};

vector<string> ChessBoard::pieces_other_than_king_can_move_to_position(string position) {
  int error;
  vector<string> pieces;
  map<string, Piece*>::iterator it;
  for(it = Board.begin(); it != Board.end(); ++it) {
    if((it->second) != nullptr &&
       (it->second)->get_colour() == get_player_turn() &&
       check_validation((it->first), position, error) &&
       !dynamic_cast<King*>(it->second)) {
      pieces.push_back((it->first));
    }
  }
  return pieces;
};

vector<string> ChessBoard::opposite_pieces_can_move_to_position(string position) {
  vector<string> pieces;
  switch_turn();
  pieces = pieces_can_move_to_position(position);
  switch_turn();
  return pieces;
};

void ChessBoard::check_promotion(string initial_position, string next_position, int& error) {
  if((white_turn && next_position[1] == '8') ||
     (!white_turn && next_position[1] == '1')){
    string piece_type;
    Colour colour;
    
    if(white_turn == true)
      colour = Colour::White;
    else
      colour = Colour::Black;

    Piece* piece = Board[initial_position];
    Board[initial_position] = nullptr;

    //Checking if the move puts own king in check and it will bet set back to previous position if so
    if(check_own(get_king_position())) {
      Board[initial_position] = piece;
      error = ERROR_PUTTING_OWN_KING_IN_CHECK;
      return;
    }

    cout << endl << "Pawn at position " << next_position << " has been promoted" << endl;
    cout << "Which piece type do you want your pawn to be promoted to?"
	 << " (type: \"Queen\", \"Rook\", \"Bishop\", \"Knight\", \"Pawn\"): \n";
    cin >> piece_type;
    cout << endl;
    while(true) {
      if(!piece_type.compare("Queen")) {
	Board[initial_position] = new Queen(colour, initial_position);
	break;
      } else if(!piece_type.compare("Rook")) {
	Board[initial_position] = new Rook(colour, initial_position);
	break;
      } else if(!piece_type.compare("Bishop")) {
	Board[initial_position] = new Bishop(colour, initial_position);
	break;
      } else if(!piece_type.compare("Knight")) {
	Board[initial_position] = new Knight(colour, initial_position);
	break;
      } else if(!piece_type.compare("Pawn")) {
	Board[initial_position] = new Pawn(colour, initial_position);
	break;
      } else {
	cerr << "Wrong piece type. Please try again:" << endl;;
	cin >> piece_type;
      }
    }
    delete piece;
    cout << "The pawn has become a " << piece_type;
  }
};

void ChessBoard::check_enpassant(string initial_position, string next_position, int& error) {
  //Captured piece will be stored and it will be set back to previous position in case of need
  Piece* captured_piece = nullptr;
  int number;
  
  string position = next_position;
  
  if(white_turn == true)
    number = 1;
  else
    number = -1;
  
  position[1] -= number;
  
  if((abs(next_position[0] - initial_position[0]) == 1) &&
     (abs(next_position[1] - initial_position[1]) == 1) &&
     Board[next_position] == nullptr &&
     Board[position] != nullptr) {
    captured_piece = Board[position];
    Board[position] = nullptr;

    //Checking if the move puts own king in check and it will bet set back to previous position if so
    if(check_own(get_king_position())) {
      Board[position] = captured_piece;
      error = ERROR_PUTTING_OWN_KING_IN_CHECK;
      return;
    }
    delete captured_piece;
    cout << endl << "Piece at position " + position + " captured en-passant";
  }
};

bool ChessBoard::check_player(string initial_position, int& error) {
  if(Board[initial_position] != nullptr) {
    if(Board[initial_position]->get_colour() == get_player_turn())
      return true;
    else {
      error = ERROR_WRONG_PLAYER;
      return false;
    }
  } else {
    error = ERROR_SOURCE_FIELD_EMPTY;
    return false;
  }
};

bool ChessBoard::check_equal_source(string initial_position, string next_position, int& error) {
  if(!initial_position.compare(next_position)) {
    error = ERROR_SOURCE_SAME_AS_DESTINATION;
    return true;
  } else
    return false;
};

bool ChessBoard::check_occupancy(string initial_position, string next_position, int& error) {
  if(Board[next_position] != nullptr &&
     Board[next_position]->get_colour() == get_player_turn()) {
    error = ERROR_OCCUPIED_BY_SAME_COLOUR;
    return true;
  } else
    return false;
};

bool ChessBoard::check_validation(string initial_position, string next_position, int& error) {
  if(check_player(initial_position, error) &&
     check_valid_field(initial_position, next_position, error) &&
     !check_equal_source(initial_position, next_position, error) &&
     !check_occupancy(initial_position, next_position, error) &&
     Board[initial_position]->check_validation(next_position, Board, error)) {
    return true;
  } else
    return false;
};

bool ChessBoard::check_valid_field(string initial_position, string next_position, int& error) {
  char current_file = initial_position[0];
  char next_file = next_position[0];
  int current_rank = stoi(initial_position.substr(1, initial_position.length()));
  int next_rank = stoi(next_position.substr(1, next_position.length()));

  if(current_file >= 'A' && current_file <= 'H' &&
     current_rank >= 1 && current_rank <= 8) {
    if(next_file >= 'A' && next_file <= 'H' &&
       next_rank >= 1 && next_rank <= 8) {
      return true;
    } else {
      error = ERROR_INVALID_SOURCE_FIELD;
      return false;
    }
  } else {
    error = ERROR_INVALID_DESTINATION_FIELD;
    return false;
  }
};

bool ChessBoard::check_castling(string text, string rook_position, int& error) {  
  transform(text.begin(), text.end(), text.begin(), ::tolower);
  if(!text.compare("castling") &&
     (!rook_position.compare("H1") ||
      !rook_position.compare("H8"))) {
    int increment;
    string king_position = get_king_position();
    vector<string> threatening_pieces;
    
    if(king_position[0] > rook_position[0])
      increment = -1;
    else
      increment = 1;
    
    string transient_king_position = king_position; transient_king_position[0] += increment;
    string new_king_position = transient_king_position; new_king_position[0] += increment;
    
    threatening_pieces = opposite_pieces_can_move_to_position(transient_king_position);
    if((dynamic_cast<King*>(Board[king_position]))->get_move() &&
       (dynamic_cast<Rook*>(Board[rook_position]))->get_move() &&
       Board[king_position]->check_clear_rank(king_position, rook_position, Board) &&
       threatening_pieces.empty()) {
      
      Board[king_position]->set_previous_position(king_position);
      Board[king_position]->set_initial_position(new_king_position);
      Board[new_king_position] = Board[king_position];
      Board[king_position] = nullptr;
      
      Board[rook_position]->set_previous_position(rook_position);
      Board[rook_position]->set_initial_position(transient_king_position);
      Board[transient_king_position] = Board[rook_position];
      Board[rook_position] = nullptr;

      //Checking if castling put own king in check and it will bet set back to previous position if so
      if(check_own(new_king_position)) {
	Board[king_position] = Board[new_king_position];
	Board[new_king_position] = nullptr;
	Board[king_position]->set_previous_position(king_position);
	Board[king_position]->set_initial_position(king_position);
	
	Board[rook_position] = Board[transient_king_position];
	Board[transient_king_position] = nullptr;
	Board[rook_position]->set_previous_position(rook_position);
	Board[rook_position]->set_initial_position(rook_position);
	
	error = ERROR_PUTTING_OWN_KING_IN_CHECK;
	return true;
      }
      cout << "Castling with Rook at position " + rook_position + "." << endl;
      return true;
    } else {
      error = ERROR_CASTLING_IMPOSSIBLE;
      return true;
    }
  }
  return false;
};

bool ChessBoard::check_game_on() {
  return game_on;
};

bool ChessBoard::check_stalemate() {
  map<string, Piece*>::iterator it;
  string position;
  int unused_error;
  Piece* captured_piece = nullptr;
  for(int rank = 1; rank <= 8; rank++) {
    for(char file = 'A'; file <= 'H'; file++) {
      position = string(1, file) + to_string(rank);
      for(it = Board.begin(); it != Board.end(); ++it) {
	if((it->second) != nullptr &&
	   (it->second)->get_colour() == get_player_turn() &&
	   check_validation((it->first), position, unused_error)) {
	  if(Board[position] != nullptr) {
	    captured_piece = Board[position];
	    Board[position] = nullptr;
	  }

	  string previous_position = Board[(it->first)]->get_previous_position();
	  string king_position = get_king_position();
	  Board[(it->first)]->set_previous_position((it->first));
	  Board[(it->first)]->set_initial_position(position);
	  Board[position] = Board[(it->first)];
	  Board[(it->first)] = nullptr;
	  
	  if(dynamic_cast<King*>(Board[position]))
	    king_position = position;
	  
	  if(!check_own(king_position)) {
	    Board[(it->first)] = Board[position];
	    Board[position] = captured_piece;
	    Board[(it->first)]->set_previous_position(previous_position);
	    Board[(it->first)]->set_initial_position((it->first));
	    return false;
	  }
	  Board[(it->first)] = Board[position];
	  Board[position] = captured_piece;
	  Board[(it->first)]->set_previous_position(previous_position);
	  Board[(it->first)]->set_initial_position((it->first));
	}
      }
    }
  }
  return true;
};

bool ChessBoard::check(string king_position) {
  vector<string> threatening_pieces = pieces_can_move_to_position(king_position);
  if(!threatening_pieces.empty())
    return true;
  else
    return false;
};

bool ChessBoard::check_own(string king_position) {
  switch_turn();
  if(check(king_position)) {
    switch_turn();
    return true;
  } else {
    switch_turn();
    return false;
  }
}

bool ChessBoard::checkmate(string king_position, string attacking_piece) {
  string destination;
  vector<string> possible_king_moves;
  vector<string> threatened_moves;
  int unused_error;
  
  switch_turn();

  //Checking possible king moves of opposite player
  for(int rank = 1; rank <= 8; rank++) {
    for(char file = 'A'; file <= 'H'; file++) {
      destination = string(1, file) + to_string(rank);
      if(check_validation(king_position, destination, unused_error))
	possible_king_moves.push_back(destination);
    }
  }
  
  switch_turn();

  //Checking if attacking piece can threaten the king
  vector<std::string> threatening_pieces;
  unsigned int number_of_threatened_moves = 0;
  for(unsigned int i = 0; i < possible_king_moves.size(); i++) {
    threatening_pieces = pieces_can_move_to_position(possible_king_moves[i]);
    if(!threatening_pieces.empty()) {
      threatened_moves.push_back(possible_king_moves[i]);
      number_of_threatened_moves++;
    }
  }
  
  switch_turn();

  //Checking if defender is able to destroy the attacking piece
  vector<string> defending_pieces = pieces_can_move_to_position(attacking_piece);
  if(!defending_pieces.empty()) {
    switch_turn();
    return false;
  }

  //Checking if the attacking piece can be blocked by the defender
  vector<string> possible_block_positions;
  string position = attacking_piece;
  int x_increase, y_increase;
  if(Board[attacking_piece]->check_clear_rank(attacking_piece, king_position, Board)) {
    if(king_position[0] - attacking_piece[0] > 0)
      x_increase = 1;
    else
      x_increase = -1;

    while(position.compare(king_position)) {
      possible_block_positions = pieces_other_than_king_can_move_to_position(position);
      if(!possible_block_positions.empty()) {
	switch_turn();
	return false;
      }
      position[0] += x_increase;
    }
    switch_turn();
    return true;
  }
  if(Board[attacking_piece]->check_clear_file(attacking_piece, king_position, Board)) {
    if(king_position[1] - attacking_piece[1] > 0)
      y_increase = 1;
    else
      y_increase = -1;
    
    while(position.compare(king_position)) {
      possible_block_positions = pieces_other_than_king_can_move_to_position(position);
      if(!possible_block_positions.empty()) {
	switch_turn();
	return false;
      }
      position[1] += y_increase;
    }
    switch_turn();
    return true;
  }
  if(Board[attacking_piece]->check_clear_diagonal(attacking_piece, king_position, Board)) {
    if(king_position[0] > attacking_piece[0] &&
       king_position[1] > attacking_piece[1]) {
      x_increase = 1;
      y_increase = 1;
    } else if(king_position[0] > attacking_piece[0] &&
	      king_position[1] < attacking_piece[1]) {
      x_increase = 1;
      y_increase = -1;
    } else if(king_position[0] < attacking_piece[0] &&
	      king_position[1] > attacking_piece[1]) {
      x_increase = -1;
      y_increase = 1;
    } else {
      x_increase = -1;
      y_increase = -1;
    }
    
    while(!position.compare(king_position)) {
      possible_block_positions = pieces_other_than_king_can_move_to_position(position);
      if(!possible_block_positions.empty()) {
	switch_turn();
	return false;
      }
      position[0] += x_increase;
      position[1] += y_increase;
    }
    switch_turn();
    return true;
  }
  
  switch_turn();

  //It is checkmate if number of possible king moves equals number of threatened moves 
  if(number_of_threatened_moves > 0 &&
     possible_king_moves.size() == number_of_threatened_moves) {
    return true;
  }
  return false;
};

void ChessBoard::print_board() {
  if(print_board_value) {
    cout << endl;
    for(int rank = 8; rank >= 1; --rank) {
      cout << to_string(rank) + "   ";
      for(char file = 'A'; file <= 'H'; file++) {
	if(Board[string(1, file) + to_string(rank)] == nullptr)
	  cout << "- ";
	else
	  cout << Board[string(1, file) + to_string(rank)]->symbol + " ";
      }
      cout << endl;
    }
    cout << endl;
    cout << "    A B C D E F G H" << endl << endl;
    cout << endl;
  }
};

void ChessBoard::print_error(string initial_position, string next_position, int error) {
  switch (error) {
  case ERROR_INVALID_SOURCE_FIELD:
    cerr << endl << "Error: " + initial_position + " is an invalid source field." << endl;
    break;
  case ERROR_INVALID_DESTINATION_FIELD:
    cerr << endl << "Error: " + next_position + " is an invalid destination field. " << endl;
    break;
  case ERROR_WRONG_PLAYER:
    cerr << endl << "Error: Wrong player." << endl;
    break;
  case ERROR_SOURCE_FIELD_EMPTY:
    cerr << endl << "Error: No piece on the source field." << endl;
    break;
  case ERROR_SOURCE_SAME_AS_DESTINATION:
    cerr << endl << "Error: Source field the same as destination." << endl;
    break;
  case ERROR_OCCUPIED_BY_SAME_COLOUR:
    cerr << endl << "Error: Destination field is already occupied." << endl;
    break;
  case ERROR_INVALID_ROOK_MOVE:
    cerr << endl << "Error: Invalid Rook move." << endl;
    break;
  case ERROR_INVALID_QUEEN_MOVE:
    cerr << endl << "Error: Invalid Queen move." << endl;
    break;
  case ERROR_INVALID_BISHOP_MOVE:
    cerr << endl << "Error: Invalid Bishop move." << endl;
    break;
  case ERROR_INVALID_KNIGHT_MOVE:
    cerr << endl << "Error: Invalid Knight move." << endl;
    break;
  case ERROR_INVALID_KING_MOVE:
    cerr << endl << "Error: Invalid King move." << endl;
    break;
  case ERROR_INVALID_PAWN_MOVE:
    cerr << endl << "Error: Invalid Pawn move." << endl;
    break;
  case ERROR_GAME_IS_OFF:
    cerr << endl << "Error: Game is off." << endl;
    break;
  case ERROR_CASTLING_IMPOSSIBLE:
    cerr << endl << "Error: Castling impossible." << endl;
    break;
  case ERROR_PUTTING_OWN_KING_IN_CHECK:
    cerr << endl << "Error: Piece cannot expose their king to check." << endl;
    break;
  }
};

void ChessBoard::print_result() {
  if(winner == Winner::White) {
    cout << "WHITE WINS!" << endl;
  } else if(winner == Winner::Black) {
    cout << "BLACK WINS!" << endl;
  } else {
    cout << "DRAW!" << endl;
  }
  cout << endl;
};

void ChessBoard::print_move(string initial_position, string next_position) {
  if(white_turn)
    cout << "White's ";
  else
    cout << "Black's ";
  cout << piece_type(initial_position) << " moves from " << initial_position
       << " to " << next_position;
};

void ChessBoard::print_capture(string next_position) {
  if(Board[next_position] != nullptr) {
    cout << " taking ";
    if(white_turn)
      cout << "Black's ";
    else
      cout << "White's ";
    cout << piece_type(next_position) << endl;
  }
  else
    cout << endl;
};

string ChessBoard::piece_type(string initial_position) {
  if(dynamic_cast<Pawn*>(Board[initial_position]))
    return "Pawn";
  else if(dynamic_cast<Rook*>(Board[initial_position]))
    return "Rook";
  else if(dynamic_cast<Queen*>(Board[initial_position]))
    return "Queen";
  else if(dynamic_cast<Knight*>(Board[initial_position]))
    return "Knight";
  else if(dynamic_cast<King*>(Board[initial_position]))
    return "King";
  else if(dynamic_cast<Bishop*>(Board[initial_position]))
    return "Bishop";
  else
    return "Empty";
};

Colour ChessBoard::get_player_turn() {
  if(white_turn == true)
    return Colour::White;
  else
    return Colour::Black;
};

string ChessBoard::get_king_position() {
  if(white_turn == true)
    return white_king_position;
  else
    return black_king_position; 
};
