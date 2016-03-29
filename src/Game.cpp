#include <cstdlib>
#include "Game.hpp"
#include <ctime>

Game::Game() : m_mainView(sf::Vector2f(0, 0), sf::Vector2f(400, 400)), m_dtServerFrame(sf::seconds(1.0/20.0f)),
               m_dtIdeal(sf::seconds(1.0/60.0f)), m_isRunning(false)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 6;
    m_window.create(sf::VideoMode(800, 800), "Siniclone", sf::Style::Default, settings);
    m_window.setView(m_mainView);
    dtSMAinit(m_dtIdeal);
    m_dtSMA = m_dtIdeal;

    circles = new sf::CircleShape[40];
    particles = new tacoTruck::Particle[40];
}

Game::~Game()
{
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
                else if (event.key.code == sf::Keyboard::W) {
                    m_mainView.move(0, -1);
                }
                else if (event.key.code == sf::Keyboard::A) {
                    m_mainView.move(-1, 0);
                }
                else if (m_isRunning && event.key.code == sf::Keyboard::S) {
                    m_mainView.move(0, 1);
                }
                else if (event.key.code == sf::Keyboard::D) {
                    m_mainView.move(1, 0);
                }
                else if (!m_isRunning && event.key.code == sf::Keyboard::S) {
                    startGame(SinglePlayer);
                }
                else if (!m_isRunning && event.key.code == sf::Keyboard::M) {
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
    rwindow.setView(m_mainView);

    for (int i = 0; i < 40; i++) {
        particles[i].integrate(dt.asSeconds());
        circles[i].setPosition(coordWorldToView((particles[i].getPosition())));
        rwindow.draw(circles[i]);
    }
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

    sf::Time dtCurrentScaled = dtCurrent / sf::Int64(m_dtSMA_period);
    m_dtSMA = m_dtSMA - m_dtHistory[idx] + dtCurrentScaled;
    m_dtHistory[idx] = dtCurrentScaled;
    idx = (idx + 1) % m_dtSMA_period;

    return m_dtSMA;
}

void Game::startGame(const GameType newGameType) {
    srand(time(NULL));
    for (int i = 0; i < 40; i++) {
        circles[i].setRadius(rand() % 10 + 5);
        circles[i].setPointCount(20);
        circles[i].setFillColor(sf::Color(128, 128, 128));
        circles[i].setOutlineColor(sf::Color::White);
        circles[i].setOutlineThickness(-2.0);

        particles[i].setPosition(rand() % 800 - 400, rand() % 800 - 400);
        particles[i].setVelocity(rand() % 60 - 30, rand() % 60 - 30);
        particles[i].setMass(0.01);
        particles[i].setDamping(0.999);
    }
    m_isRunning = true;
}

sf::Vector2f Game::coordWorldToView(const tacoTruck::Vector2D coord) const {
    return sf::Vector2f(coord.x, -coord.y);
}

tacoTruck::Vector2D Game::coordViewToWorld(const sf::View & view, const sf::Vector2f & coord) {
    return tacoTruck::Vector2D();
}
