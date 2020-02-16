#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop(Colour colour, string initial_position);
        virtual ~Bishop();
	//Check if a destination move is valid or not
        bool check_validation(string next_position, map<string, Piece*> Board, int& error);
};

#endif
