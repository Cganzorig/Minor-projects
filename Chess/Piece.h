#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include "errors.h"

using namespace std;

enum class Colour {White, Black};

class Piece {
    friend class ChessBoard;
    public:
        Colour colour;
        string initial_position;
        string previous_position;
        string symbol;

        Piece(Colour colour, string initial_position);
        virtual ~Piece();
		//Accessing functions
        Colour get_colour();
        string get_initial_position();
        string get_previous_position();
		//Modifier
        void set_initial_position(string temp_position);
        void set_previous_position(string temp_position);
		//Check if a destination move is in the same rank, file, diagonal or not
        bool check_same_rank(string first_position, string second_position);
        bool check_same_file(string first_position, string second_position);
        bool check_same_diagonal(string first_position, string second_position);
		//Check if en route to a destination move is obstructed or not
        bool check_clear_rank(string first_position, string second_position, map<string, Piece*> Board);
        bool check_clear_file(string first_position, string second_position, map<string, Piece*> Board);
        bool check_clear_diagonal(string first_position, string second_position, map<string, Piece*> Board);
		//Virtual function to check if a destination move is valid or not
        virtual bool check_validation(string nextPosition, map<string, Piece*> Board, int& errorCode) = 0;
};

#endif
