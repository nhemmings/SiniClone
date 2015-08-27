#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "CoordAdapter.hpp"
#include "AsteroidPool.hpp"

class Game
{
private:
    enum GameType {SinglePlayer, MultiPlayer};

    /**
     *  Adapter class to convert between the differing coordinate systems of the physics and graphics engines.
     *  Specifically, SFML puts the origin in the top left corner of the window and the Y-axis increases down. The
     *  physics engine puts the origin in the lower left and the Y-axis increases upward, which is more intuitive for
     *  physics simulation (i.e. gravity). This class provides helper functions to convert from one to the other.
     */
    class SFMLCoordAdapter : public CoordAdapter {
    public:
        SFMLCoordAdapter(const Vector2u windowSize) : CoordAdapter(windowSize) {}
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
    static const unsigned short m_dtHistorySize = 10;
    sf::Time m_dtSMA;
    sf::Time m_dtHistory[m_dtHistorySize];

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
