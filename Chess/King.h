#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    private:
        bool initial_move;
    public:
        King(Colour colour, string initial_position);
        virtual ~King();
	//Accessing functions
        bool get_move();
	//Modifier
        void set_move(bool temp);
	//Check if a destination move is valid or not
        bool check_validation(string next_position, map<string, Piece*> Board, int& error);
};
#endif
