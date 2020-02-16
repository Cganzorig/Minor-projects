#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Piece;

class Queen : public Piece {
    public:
        Queen(Colour colour, string initial_position);
        virtual ~Queen();
        //Check if a destination move is valid or not
	bool check_validation(string next_position, map<string, Piece*> Board, int& error);
};

#endif
