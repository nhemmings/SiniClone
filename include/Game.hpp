#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
public:
    struct config {
        sf::Uint8 serverTargetFPS;
        sf::Uint8 clientTargetFPS;
    };
private:
    sf::RenderWindow m_window;
    const sf::Time m_tServerFrame;
    const sf::Time m_dtIdeal;
    void runServerFrame(const sf::Time & dt);
    void runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow);
public:
    Game();
    virtual ~Game();

    void run();
protected:
};

#endif // GAME_HPP
