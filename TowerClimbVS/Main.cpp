#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "Game.h"

int main()
{
    // Initialise the RNG
    srand(time(NULL));

    // Create the game
    Game gameInstance; // default constructor

    // This will not end until the game is over
    gameInstance.RunGameLoop();

    // If the loop exits, game is over. End the program.
    return 0;
}