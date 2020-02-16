#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

enum class Winner {White, Black, Draw};

class ChessBoard {
    private:
        map<string, Piece*> Board;
        Winner winner;
        string white_king_position;
        string black_king_position;
        bool white_turn;
        bool game_on;
        bool print_board_value;
    public:
        ChessBoard();
        ~ChessBoard();

        void submitMove(string initial_position, string next_position);
        void resetBoard(); //Reset board
        void board_setup(); //Initialise board
        void clean(); //Clean board
        void switch_turn(); //Switch player's turn

	//Accessing functions
        Colour get_player_turn();
        string get_king_position();

	//Function that returns type of piece
        string piece_type(string initial_position);

	//Function that returns vector of position of opposite pieces to a given position
        vector<string> pieces_can_move_to_position(string position);
        vector<string> pieces_other_than_king_can_move_to_position(string position);
        vector<string> opposite_pieces_can_move_to_position(string position);

	//Check if promotion or enpassant conditions are met or not
        void check_promotion(string initial_position, string next_position, int& error);
        void check_enpassant(string initial_position, string next_position, int& error);

	//Check if a move is valid or not using following methods
        bool check_player(string initial_position, int& error);
        bool check_equal_source(string initial_position, string next_position, int& error);
        bool check_occupancy(string initial_position, string next_position, int& error);
        bool check_validation(string initial_position, string next_position, int& error);
        bool check_valid_field(string initial_position, string next_position, int& error);
        bool check_castling(string text, string rook_position, int& error);

	//Functions that return state of game
        bool check_game_on();
        bool check_stalemate();
        bool check(string king_position);
        bool check_own(string king_position);
        bool checkmate(string king_position, string attacking_piece);

	//Printing
        void print_board();
        void print_error(string initial_position, string next_position, int error);
        void print_result();
        void print_move(string initial_position, string next_position);
        void print_capture(string next_position);
};

#endif
