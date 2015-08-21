#include "Game.hpp"

Game::Game() : m_window(sf::VideoMode(800, 600), "SFML works!"), m_tServerFrame(sf::seconds(1.0/20.0f)),
               m_dtIdeal(sf::seconds(1.0/30.0f))
{
    dtSMAinit(m_dtIdeal);
}

Game::~Game()
{
    //dtor
}

void Game::run() {
    using sf::Time;
    using sf::Clock;

    // Initialize clocks
    Time dtReal = m_dtIdeal;           // The real frame delta time, initialized to ideal value
    Time dtServer = sf::Time::Zero;    // Delta time since last server frame
    Clock realTimeClock;
    Time tBegin = realTimeClock.getElapsedTime();

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

        // Server update
        dtServer += dtReal;
        if (dtServer >= m_tServerFrame) {
            runServerFrame(dtServer);
            dtServer -= m_tServerFrame;
        }

        // Client update
        runClientFrame(dtReal, m_window);

        // Timer update
        Time tEnd = realTimeClock.getElapsedTime();
        Time dtThisFrame = tEnd - tBegin;
        dtReal = dtSMAupdate(dtThisFrame);
        tBegin = tEnd;

        m_window.display();
    }
}

void Game::runServerFrame(const sf::Time & dt) {

}

void Game::runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow) {
    rwindow.clear();
    rwindow.display();
}

void Game::dtSMAinit(const sf::Time & dtIdeal) {
    for (int i = 0; i < m_dtHistorySize; i++) {
        m_dtHistory[i] = dtIdeal;
    }
}

sf::Time Game::dtSMAupdate(const sf::Time & dtCurrent) {
    static unsigned short idx = 0;
    m_dtSMA += dtCurrent/float(m_dtHistorySize) - m_dtHistory[idx]/float(m_dtHistorySize);
    m_dtHistory[idx] = dtCurrent;
    idx = (idx + 1) % m_dtHistorySize;
    return m_dtSMA;
}
