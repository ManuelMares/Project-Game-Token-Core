#include <vector>
#include "Game_token.h" 
#include "Board_space.h"
#include "Board.h"

namespace Grid_game
{
    bool moveToLeft = false;

    int oldX = 0;
    int oldY = 0;
    void Token::move(direction dir){
        oldX = x;
        oldY = y;
        
        //cout << "dir:" << dir << "=====================\n";

        Space::terrain_type element = board.retrieve_space(x,y).type();

        if(dir == 0){
            if( 0 == y )
                return;
            //
            --y;
        } 
        else if(dir == 2){
            if( board.height() == y )
                return;
            y++;
        } 
        else if(dir == 1){
            if( board.width() == x )
                return;
            x++;
        } 
        else if(dir == 3){
            if( 0 == x ){
                return; 
            }
            --x;
        } 
        apply_terrain_effect(element); 

    }
    
    void Token::move_special(vector<direction> vDir){
        
        //cout <<"(*&^%$@$#%^&*^%$#!#@%^&&^%$!$@#^&^%!$@%#^$^&%$!@%#^$&^%565";
        for (int i = 0; i < vDir.size(); i++)
        {
            move(vDir[i]);
        }
        
        //move(vDir[0]);
    }

    void Token::apply_terrain_effect(const Space::terrain_type terr){
       
        try
        {
          //  Space::terrain_type element = board.retrieve_space(x,y).type();
            
                ////cout <<  " TERR " << terr << "========================\n\n\n";
            //e == 0  is free
           if(terr == 0) {
                //nothing
                ////cout << "GOT INTO NOTHING!==========================================";
                return;
            } 
            //b == 1 is a wall
            if(terr == 1) {
                //cannot move, we have to return
                //i think we need to call move() and make it go in a different direction
                //or go back to where it was before trying to step into b

                //if I hit the barrier, I move back instead of down. 
                //These two movements compensate the previous down movemente, and send me right
                /*
                x++;
                --y;

                //if new position is wall, go left

                if(moveToLeft){

                    x = x -2;

                    if(x ==  0){
                        moveToLeft = false;
                    }
                    if( x == -1)
                        hp = 0;
                    return;
                }
                ////cout << "GOT INTO BARRIER!==========================================\n";
                
                if( board.width()-1 == x){
                    moveToLeft = true;
                }

                */
                x =oldX;
                y =oldY;
                return;
            }
            //w == 2 is water
            if(terr == 2) {
                //reduce hp and pp
                ////cout << "GOT INTO WATER!==========================================";
                --hp;
                --pp;
                //check if we died is managed by game_state
            }
            //l == 3 is lava
            if(terr == 3) 
            {
                ////cout << "GOT INTO LAVA!==========================================";
                hp = 0;
            }
        }
        
        catch(const std::exception& e)
        {
            //cout << "EXCEPTION===============================";
            hp = 0;
        }
        
    }
}