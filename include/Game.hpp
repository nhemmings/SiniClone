#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "CoordAdapter2D.hpp"
#include "AsteroidPool.hpp"

#ifdef DEBUG
#include <fstream>
#endif // DEBUG

/**
 *  The primary game logic and entry point. Initializes the game's subsystems and manages the viewing window.
 */
class Game
{
private:
    enum GameType {SinglePlayer, MultiPlayer};

    /**
     *  Provides helper functions to convert between the SFML coordinate system and the physics engine's coordinate
     *  system.SFML puts the origin in the top left corner of the window and the Y-axis increases down. The physics
     *  engine puts the origin in the lower left and the Y-axis increases upward, which is more intuitive for physics
     *  simulation (e.g. gravity).
     */
    class SFMLCoordAdapter : public CoordAdapter2D {
    public:
        SFMLCoordAdapter(const Vector2u windowSize) : CoordAdapter2D(windowSize) {}
        float physToWindowX(const float x) const;
        float physToWindowY(const float y) const;
        Vector2u physToWindow(const Vector2D& vec) const;

        float windowToPhysX(const float x) const;
        float windowToPhysY(const float y) const;
        Vector2D windowToPhys(const Vector2u& vec) const;
    };

    GameType m_GameType;
    sf::RenderWindow m_window;
    const sf::Time m_dtServerFrame;
    const sf::Time m_dtIdeal;
    SFMLCoordAdapter m_CoordAdapter;
    AsteroidPool m_AsteroidPool;
    bool m_isRunning;

    /* Data for tracking a Simple Moving Average of delta times */
    static const unsigned short m_dtSMA_period = 10;
    sf::Time m_dtSMA;
    sf::Time m_dtHistory[m_dtSMA_period];

    #ifdef DEBUG
    std::ofstream m_outFile;
    #endif // DEBUG

    void startGame(const GameType newGameType);
    void runServerFrame(const sf::Time & dt);
    void runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow);
    void dtSMAinit(const sf::Time & dtIdeal);
    sf::Time dtSMAupdate(const sf::Time & dtCurrent);
public:
    Game();
    virtual ~Game();

    void run();
};

#endif // GAME_HPP
