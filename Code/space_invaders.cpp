// space_invaders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"
#include <iostream>
#include <time.h>
#include "SFML/Audio.hpp"

int main()
{
   
    Game game{};
    game.run();
    
    
    

    return 0;

}


//to add: level file loading and rendering
    //special enemy that stays on screen, moves side to side, has lots of health, and shoots at you
    //items?
    //Background
