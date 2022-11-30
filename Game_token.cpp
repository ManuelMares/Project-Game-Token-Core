#include <vector>
#include "Game_token.h" 
#include "Board_space.h"
#include "Board.h"

//I worked together with Trang Tran

namespace Grid_game
{
    int oldX = 0; 
    int oldY = 0; 

    void Token::move(direction dir){
            oldX = x; 
            oldY = y; 

        if(dir == 0){
            if( 0 == y )
                return;
            --y;
        } 
        else if(dir == 2){
            if( board.height() == y )
                return;
            y++;
        } 
        else if(dir == 1){
            if( board.width()-1 == x )
                return;
            x++;
        } 
        else if(dir == 3){
            if( 0 == x ){
                return; 
            }
            --x;
        } 
    }
    
    void Token::move_special(vector<direction> vDir){
        move(vDir[0]);
    }

    void Token::apply_terrain_effect(const Space::terrain_type terr){
            //empty space
           if(terr == 0) {
                return;
            } 

            //wall / barrier
            else if(terr == 1) {
                x = oldX; 
                y = oldY;
                return;
            }

            //water 
            else if(terr == 2) {
                //reduce hp and pp
                --hp;
                --pp;
                return;
            }

            //lava
            else if(terr == 3) 
            {
                hp = 0;
                pp = 0;
                return; 
            }
        
        
    }
}
