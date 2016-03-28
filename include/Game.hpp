#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "particle.hpp"
#include "Vector2D.hpp"

/**
 *  The primary game logic and entry point. Initializes the game's subsystems and manages the viewing window.
 */
class Game
{
private:
    enum GameType {SinglePlayer, MultiPlayer}; /**< Enumeration of game modes. */

    GameType m_GameType;
    sf::RenderWindow m_window;
    sf::View m_mainView;
    const sf::Time m_dtServerFrame;
    const sf::Time m_dtIdeal;
    bool m_isRunning;

    /**< Data for tracking a Simple Moving Average of frame delta times */
    static const sf::Uint8 m_dtSMA_period = 10;
    sf::Time m_dtSMA;
    sf::Time m_dtHistory[m_dtSMA_period];

    void startGame(const GameType newGameType);
    void runServerFrame(const sf::Time & dt);
    void runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow);

    void dtSMAinit(const sf::Time & dtIdeal);
    sf::Time dtSMAupdate(const sf::Time & dtCurrent);

    sf::CircleShape* circles;
    physics::Particle* particles;

    sf::Vector2f coordWorldToView(const physics::Vector2D coord) const;
    physics::Vector2D coordViewToWorld(const sf::View & view, const sf::Vector2f & coord);
public:
    Game();
    virtual ~Game();

    int run();
};
#endif // GAME_HPP
