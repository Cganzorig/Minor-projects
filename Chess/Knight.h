#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
    public:
        Knight(Colour colour, string initial_position);
        virtual ~Knight();
		//Check if a destination move is valid or not
        bool check_validation(string next_position, map<string, Piece*> Board, int& error);
};

#endif

