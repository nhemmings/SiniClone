#include "Game.hpp"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

Game::Game() : m_dtServerFrame(sf::seconds(1.0/20.0f)), m_dtIdeal(sf::seconds(1.0/1500.0f)),
               m_CoordAdapter(Vector2u(800,600)), m_AsteroidPool(m_CoordAdapter), m_isRunning(false)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 6;
    m_window.create(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
    dtSMAinit(m_dtIdeal);
    m_dtSMA = m_dtIdeal;
}

Game::~Game()
{
    //dtor
}

void Game::run() {
    #ifdef DEBUG
    using std::cout;
    using std::endl;
    cout << "(S) for Singleplayer\n(M) for Multiplayer" << endl;
    #endif // DEBUG

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
            #ifdef DEBUG
            std::cout << "Running server frame: " << realTimeClock.getElapsedTime().asSeconds() << "("
                      << dtServer.asSeconds() << ")" << std::endl;
            #endif // DEBUG
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
}

void Game::runServerFrame(const sf::Time & dt) {
}

void Game::runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow) {
    #ifdef DEBUG
    std::cout << dt.asSeconds() << std::endl;
    #endif // DEBUG

    rwindow.clear();
    m_AsteroidPool.updateAsteroids(dt);
    m_AsteroidPool.renderAsteroids(rwindow);
    rwindow.display();
}

void Game::dtSMAinit(const sf::Time & dtIdeal) {
    for (int i = 0; i < m_dtHistorySize; i++) {
        m_dtHistory[i] = dtIdeal;
    }
}

sf::Time Game::dtSMAupdate(const sf::Time & dtCurrent) {
    static unsigned short idx = 0;
    m_dtSMA = m_dtSMA * float(m_dtHistorySize - 1)/float(m_dtHistorySize) + dtCurrent/float(m_dtHistorySize);
    m_dtHistory[idx] = dtCurrent;
    idx = (idx + 1) % m_dtHistorySize;
    return m_dtSMA;
}

void Game::startGame(const GameType newGameType) {
    m_GameType = newGameType;

    #ifdef DEBUG
    std::cout << "Starting new game with type: " <<
                 ((newGameType == 0) ? "SinglePlayer" : "MultiPlayer") << std::endl;
    std::cout << "Spawning asteroid at (25, 50) with velocity (0, 0) and acceleration (0, 0)" << std::endl;
    #endif // DEBUG

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
