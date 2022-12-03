#include <vector>
#include "Game_token.h" 
#include "Board_space.h"
#include "Board.h"
#include <map>
#include <algorithm>
#include <map> 

namespace Grid_game
{
    vector<vector<int>> matrixMaze(10, std::vector<int>(10));
    vector<string> stackDirections = {};
    bool solutionFound = false;

    std::map<string, int> goal = {
        { "X", 0 },
        { "Y", 0 }
    };

    
    void Token::getGoal(){
        //This function gets the positions of the goal
        //the goal is in the second to last row

        goal["Y"] = board.height() -2;
        for (int xIndex = 0; xIndex < board.width(); xIndex++)
        {
            //cout << ", TYPE: " <<board.retrieve_space( xIndex, goal["Y"] ).type();
            //if goal found
            if( board.retrieve_space( xIndex, goal["Y"] ).type() == 0 )
                goal["X"] = xIndex;
            
        }
    }

    void Token::getMaze(){
        for(int indexColumn = 0; indexColumn < board.width(); indexColumn++){
            for(int indexRow = 0; indexRow < board.height(); indexRow++){
                matrixMaze[indexRow][indexColumn] = board.retrieve_space(indexRow, indexColumn).type();     
            }
        }
    }

    void Token::move(direction dir){   
        if(!solutionFound){
            //move just call move_special overloaded with no parameters
            int xn = board.get_start_position().first;
            int yn = board.get_start_position().second;
            cout << "xn: " << x << "\n";
            cout << "yn: " << y << "\n";

            getGoal();
            cout << "goal[\"X\"]: " << goal["X"] << "\n";
            cout << "goal[\"Y\"]: " << goal["Y"] << "\n";

            //get the solution
            solveMaze(xn, yn, "DUMMY");
            std::reverse(stackDirections.begin(), stackDirections.end());
            cout << "GOT SOLUTION \n";
            return;
        }

        cout << "x: " << x << "\n";
        cout << "y: " << y << "\n"; 

        //solve the maze
        printStackDirections();
        move_special();
    }
    
    void Token::move_special(vector<direction> vDir){
        move(vDir[0]);
    }

    void Token::solveMaze(int xn, int yn, string direction){


            

        //if it finds water a third time, is like a wall, go back
        stackDirections.push_back(direction);
        printStackDirections();
            cout << "goal[\"X\"]: " << goal["X"] << "\n";
            cout << "goal[\"Y\"]: " << goal["Y"] << "\n";
        cout << "Xn: " << xn << "\n";
        cout << "Yn: " << yn << "\n";
        
        //the direction has to be added to the stack with every movement
        //if it was wrong, it gets deleted at the exit of the method, in the validations

        //===============VALIDATIONS==================
        //IN CASE OF AN UNDESIRED LOOP
        if(stackDirections.size() >= 50){
            solutionFound = true;
            return;
        }


        //If out of the board, return
        if (xn < 0 || yn < 0 || xn >= board.width() || yn >= board.height()){
            cout << "ups!, out of the board \n";
            stackDirections.pop_back();
            return;
        }

        // 0 free(e); 1 barrier(b); 2 water(w); 3 lava(l)
        int effect = board.retrieve_space(xn, yn).type();

        if(effect == 1 || effect == 3){
            //blocked road or lava, go back
            cout << "ups!, barrier \n";
            stackDirections.pop_back();
            return;
        }
        

        //======================= CHECK IF THE GOAL WAS REACHED
        if( xn == goal["X"] && yn == goal["Y"]){
            //answer was found
            cout << "solution found!\n";
            stackDirections.push_back("DOWN");
            solutionFound = true;
            return;
        }

        //===================== RECURSIVE CALL
                //to scape upwards (avoid loops)
                if(direction == "UP"){
                    //try to scape to the sides
                    solveMaze(xn-1, yn, "LEFT");
                    if(solutionFound) return;

                    solveMaze(xn+1, yn, "RIGHT");
                    if(solutionFound) return;

                    //or keep going up
                    solveMaze(xn, yn-1, "UP");
                    if(solutionFound) return;
                }

        //go down
        solveMaze(xn, yn+1, "DOWN");
        if(solutionFound) return;

                //to look for exits in the sides (avoid loops)
                if(direction == "LEFT"){
                    solveMaze(xn-1, yn, "LEFT");
                    if(solutionFound) return;
                }
                if(direction == "RIGHT"){
                    solveMaze(xn+1, yn, "RIGHT");
                    if(solutionFound) return;
                }

        //go left
        solveMaze(xn-1, yn, "LEFT");
        if(solutionFound) return;
        //go right
        solveMaze(xn+1, yn, "RIGHT");
        if(solutionFound) return;
        //go up
        solveMaze(xn, yn-1, "UP");
        if(solutionFound) return;
    }
    
    void Token::move_special(){ 
            cout << "goal[\"X\"]: " << goal["X"] << "\n";
            cout << "goal[\"Y\"]: " << goal["Y"] << "\n";
        
        string newMovement = stackDirections[ stackDirections.size() - 1];
        stackDirections.pop_back();

        cout << "new movement: " + newMovement + "\n";

        if( newMovement == "UP")
            --y;
        if( newMovement == "DOWN")
            y++;
        if( newMovement == "RIGHT")
            x++;
        if( newMovement == "LEFT")
            --x;
    }

    void Token::printStackDirections(){
        int length = stackDirections.size();
        if(length == 0)
            return;
            
        cout << "[";
        for (int index = 0; index < length; index++)
        {   
            //Go in reverse. It is a stack!
            cout << stackDirections[length - index - 1] << ", ";
        }
        cout << "]\n";
        
    }

    void Token::apply_terrain_effect(const Space::terrain_type terr){
       
        // 0 free(e)
        // 1 barrier(b)
        // 2 water(w)
        // 3 lava(l)

        //empty space
        if(terr == 0) {
            return;
        } 

        //wall / barrier
        else if(terr == 1) {
            hp = 0;
            pp = 0;
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