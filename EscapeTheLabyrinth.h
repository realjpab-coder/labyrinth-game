#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change constant kYourNetID to store your netID 
 *    - your submission will be manually inspected to ensure
 *      you have used the exact string that is your netID
 *    - thus, it is vital you understand what your netID is
 *    - ex: Professor Reckinger's email is scotreck@uic.edu, so
 *          Professor Reckinger's netID is scotreck         
 *    - ex: Student Sparky's email is sspark211@uic.edu, so
 *          Student Sparky's netID is sspark211 
 * WARNING: Once you've set set this constant and started 
 * exploring your maze, do NOT edit the value of kYourNetID. 
 * Changing kYourNetID will change which maze you get back, 
 * which might invalidate all your hard work!
 */
const string kYourNetID = "jpabi2";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "SSENNSSENNESNWSSSWW";
const string kPathOutOfTwistyMaze = "NNSENEWNWNES";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    bool hasSpellbook = false;
    bool hasWand = false;
    bool hasPotion = false;
    MazeCell* curr = start;

    if (start->whatsHere == "Spellbook"){
        hasSpellbook = true;
    }
    else if (start->whatsHere == "Wand"){
        hasWand = true;
    }
    else if(start->whatsHere == "Potion"){
        hasPotion = true;
    }
    
    for (char move : moves){
        if (move == 'N'){
            if (curr->north == nullptr){
                return false;
            }
            curr = curr->north;
        }
        else if (move == 'E'){
            if (curr->east == nullptr){
                return false;
            }
            curr = curr->east;
        }
        else if (move == 'S'){
            if (curr->south == nullptr){
                return false;
            }
            curr = curr->south;
        }
        else if (move == 'W'){
            if (curr->west == nullptr){
                return false;
            }
            curr = curr->west;
        }
        else{
            return false;
        }

        if (curr->whatsHere == "Spellbook"){
            hasSpellbook = true;
        }
        else if (curr->whatsHere == "Wand"){
            hasWand = true;
        }
        else if(curr->whatsHere == "Potion"){
            hasPotion = true;
        }
    }
    return hasSpellbook && hasWand && hasPotion;
}
