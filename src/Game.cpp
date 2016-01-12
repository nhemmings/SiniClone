#include <cstdlib>
#include "Game.hpp"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

Game::Game() : m_dtServerFrame(sf::seconds(1.0/20.0f)), m_dtIdeal(sf::seconds(1.0/1500.0f)),
               m_CoordAdapter(Vector2u(800,600)), m_AsteroidPool(m_CoordAdapter, 25), m_isRunning(false)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 6;
    m_window.create(sf::VideoMode(800, 600), "Siniclone", sf::Style::Default, settings);
    dtSMAinit(m_dtIdeal);
    m_dtSMA = m_dtIdeal;

    #ifdef DEBUG
    m_outFile.open("dtSMA.csv");
    #endif // DEBUG
}

Game::~Game()
{
    m_outFile.close();
}

int Game::run() {
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
            else if (event.type == sf::Event::Resized) {
                m_mainView.setCenter(m_window.getView().getCenter());
                m_mainView.setSize(event.size.width, event.size.height);
                m_window.setView(m_mainView);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    m_window.close();
                else if (event.key.code == sf::Keyboard::S && !m_isRunning) {
                    startGame(SinglePlayer);
                } else if (event.key.code == sf::Keyboard::M && !m_isRunning) {
                    startGame(MultiPlayer);
                }
            }
        }

        // Server update
        dtServer += dtReal;
        if (dtServer >= m_dtServerFrame) {
            runServerFrame(dtServer);
            dtServer -= m_dtServerFrame;
        }

        // Client update
        runClientFrame(dtReal, m_window);

        // Timer update
        Time tEnd = realTimeClock.getElapsedTime();
        Time dtThisFrame = tEnd - tBegin;
        dtReal = dtSMAupdate(dtThisFrame);
        tBegin = tEnd;
    }
    return 0;
}

void Game::runServerFrame(const sf::Time & dt) {
}

void Game::runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow) {
    rwindow.clear();
    m_AsteroidPool.updateAsteroids(dt);
    m_AsteroidPool.renderAsteroids(rwindow);
    rwindow.display();
}

void Game::dtSMAinit(const sf::Time & dtIdeal) {
    m_dtHistory[0] = dtIdeal / sf::Int64(m_dtSMA_period);
    for (int i = 1; i < m_dtSMA_period; i++) {
        m_dtHistory[i] = m_dtHistory[0];
    }
}

sf::Time Game::dtSMAupdate(const sf::Time & dtCurrent) {
    static unsigned short idx = 0;

    #ifdef DEBUG
    m_outFile << dtCurrent.asSeconds() << ",";
    #endif // DEBUG

    sf::Time dtCurrentScaled = dtCurrent / sf::Int64(m_dtSMA_period);
    m_dtSMA = m_dtSMA - m_dtHistory[idx] + dtCurrentScaled;
    m_dtHistory[idx] = dtCurrentScaled;
    idx = (idx + 1) % m_dtSMA_period;

    #ifdef DEBUG
    m_outFile << m_dtSMA.asSeconds() << std::endl;
    #endif // DEBUG

    return m_dtSMA;
}

void Game::startGame(const GameType newGameType) {
    m_GameType = newGameType;
    m_AsteroidPool.addAsteroid(10, 40, 10, 0.99, Vector2D(20, 20), Vector2D(40.0, 100.0), Vector2D(0.0, -10.0));
    m_AsteroidPool.addAsteroid(10, 40, 10, 0.99, Vector2D(780, 20), Vector2D(-40.0, 100.0), Vector2D(0.0, -10.0));
    m_isRunning = true;
}

//**********************************************************************************************************************
//  SFMLCoordAdapter Methods
//**********************************************************************************************************************
inline float Game::SFMLCoordAdapter::physToWindowX(const float x) const {
    return x;
}

inline float Game::SFMLCoordAdapter::physToWindowY(const float y) const {
    return (m_WindowSize.y - y);
}

inline Vector2u Game::SFMLCoordAdapter::physToWindow(const Vector2D& vec) const {
    return Vector2u(vec.x, m_WindowSize.y - vec.y);
}

inline float Game::SFMLCoordAdapter::windowToPhysX(const float x) const {
    return x;
}

inline float Game::SFMLCoordAdapter::windowToPhysY(const float y) const {
    return (m_WindowSize.y - y);
}

inline Vector2D Game::SFMLCoordAdapter::windowToPhys(const Vector2u& vec) const {
    return Vector2D(vec.x, vec.y);
}
