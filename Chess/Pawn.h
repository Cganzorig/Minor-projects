#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    private:
        bool initial_move;
    public:
        Pawn(Colour colour, string initial_position);
        virtual ~Pawn();
		//Modifier
        void set_move(bool temp);
		//Check if a pawn can move one step or two steps forward
        bool check_two_steps_forward(string next_position, map<string, Piece*> Board, int sign);
        bool check_one_step_forward(string next_position, map<string, Piece*> Board, int sign);
        bool check_capture(string next_position, map<string, Piece*> Board, int sign);
        bool check_enpassant(string next_position, map<string, Piece*> Board, int sign);
		//Check if a destination move is valid or not
        bool check_validation(string next_position, map<string, Piece*> Board, int& error);
};

#endif
