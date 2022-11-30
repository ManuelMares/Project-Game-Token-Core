#include <vector>
#include "Game_token.h" 
#include "Board_space.h"
#include "Board.h"


namespace Grid_game
{
    
    void move_special(vector<direction> vDir) {
            cout <<"(*&^%$@$#%^&*^%$#!#@%^&&^%$!$@#^&^%!$@%#^$^&%$!@%#^$&^%565";
        for (int i = 0; i < vDir.size(); i++)
        {
            move(vDir[i]);
        }
    }; 
        
}