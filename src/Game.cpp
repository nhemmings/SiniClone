#include "Game.hpp"

Game::Game() : m_window(sf::VideoMode(800, 600), "SFML works!"), m_tServerFrame(sf::seconds(1.0/20.0f))
{
}

Game::~Game()
{
    //dtor
}

void Game::run() {
    // MAIN GAME LOOP
    while (m_window.isOpen())
    {
        // System message pump
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    m_window.close();
            }
        }

        m_window.display();
    }
}
