#ifndef GAME_TOKEN_SPECIAL_H
#define GAME_TOKEN_SPECIAL_H

#include <vector>
#include "Board_space.h"
#include "Board.h"
#include "Game_token.h"

namespace Grid_game
{
    class Token_special : public Token
    {
        public: 
            Token_special(int init_hp, int init_pp, const Board &the_board) 
                :Token ( init_hp, init_pp, the_board){

                    cout << "asdfasdfadsfasdfasdf";
                } 

            void move_special(vector<direction> vDir) override; 
        
    };
}

#endif