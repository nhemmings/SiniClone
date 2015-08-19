/**
 *  Program bootstrap.
 *
 *  Parses command line arguments, loads any preliminary dependencies, displays splash/loading window/screen, and passes
 *  execution off to the primary Game object.
 */
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

class dtAverage {
private:
    static const unsigned short dtHistorySize = 10;
    sf::Time dtSMA;
    sf::Time dtHistory[dtHistorySize];
    unsigned short idx;
public:
    dtAverage(const sf::Time & dtIdeal);
    sf::Time update(sf::Time & dtCurrent);
};

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
    // STUB: No dependencies at this time

    // Create main Game object and pass off execution
    Game theGame;
    theGame.run();

/*
 *     dtAverage m_dtAvg(s_dtIdeal);
 */

    return 0;
}

dtAverage::dtAverage(const sf::Time & dtIdeal) : dtSMA(dtIdeal), idx(0) {
    for (int i = 0; i < dtHistorySize; i++) {
        dtHistory[i] = dtIdeal;
    }
}

sf::Time dtAverage::update(sf::Time & dtCurrent) {
    dtSMA = dtSMA + dtCurrent/float(dtHistorySize) - dtHistory[idx]/float(dtHistorySize);
    dtHistory[idx] = dtCurrent;
    idx = (idx + 1) % dtHistorySize;
    return dtSMA;
}
