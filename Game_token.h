#ifndef GAME_TOKEN_H
#define GAME_TOKEN_H

#include <vector>
#include "Board_space.h"
#include "Board.h"
#include "Game_token_base.h"

namespace Grid_game
{
    class Token : public Token_base
    {
    public: 
        
        Token(int init_hp, int init_pp, const Board &the_board) 
        : Token_base(the_board.get_start_position().first, the_board.get_start_position().second, init_hp, init_pp, the_board){
        }
            
        void move(direction dir) override;
        virtual void move_special(vector<direction> vdir) override; 
        void apply_terrain_effect(const Space::terrain_type terr) override; 

    };
}

#endif