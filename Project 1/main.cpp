#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>

#include "Zombie.h"
#include "Player.h"
#include "globals.h"
#include "Arena.h"
#include "Game.h"

using namespace std;

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    //Game g(7, 8, 25);
    Game g(3,4,2);

    // Play the game
    g.play();
}

