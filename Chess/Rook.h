#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Piece;

class Rook : public Piece {
    private:
        bool initial_move;
    public:
	Rook(Colour colour, string initial_position);
	virtual ~Rook();
	//Accessing functions
	bool get_move();
	//Modifier
	void set_move(bool temp); 
	//Check if a destination move is valid or not
	bool check_validation(string next_position, map<string, Piece*> Board, int& error);
};

#endif
