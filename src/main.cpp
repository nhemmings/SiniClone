/** @file
 *  Program bootstrap.
 *
 *  Parses command line arguments, loads any preliminary dependencies, displays splash/loading window/screen, and passes
 *  execution off to the primary Game object.
 */
#include "Game.hpp"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

/**
 *  Program entry point.
 */
int main(int argc, char** argv)
{
    #ifdef DEBUG
    using std::cout;
    using std::endl;
    #endif // DEBUG

    // Parse command line arguments
    if (argc > 1) {
        // STUB: Process command line arguments
    }

    // Load and display splash/loading window
    // STUB: Splash can be developed later

    // Load dependencies

    // Create main Game object and pass off execution
    Game theGame;
    return theGame.run();
}
