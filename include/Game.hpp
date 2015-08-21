#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
private:
    sf::RenderWindow m_window;
    const sf::Time m_tServerFrame;
    const sf::Time m_dtIdeal;

    /* Data for tracking a Simple Moving Average of delta times */
    static const unsigned short m_dtHistorySize = 10;
    sf::Time m_dtSMA;
    sf::Time m_dtHistory[m_dtHistorySize];

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
