#include <cstdlib>
#include "Game.hpp"
#include <ctime>

#include <iostream>

#define numParticles 5

Game::Game() : m_mainView(sf::Vector2f(400, 300), sf::Vector2f(800, 600)), m_dtServerFrame(sf::seconds(1.0/20.0f)),
               m_dtIdeal(sf::seconds(1.0/60.0f)), m_isRunning(false)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 6;
    m_window.create(sf::VideoMode(800, 600), "Siniclone", sf::Style::Default, settings);
    m_window.setView(m_mainView);
    dtSMAinit(m_dtIdeal);
    m_dtSMA = m_dtIdeal;

    circles = new sf::CircleShape[40];
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
                else if (event.key.code == sf::Keyboard::R) {
                    m_isRunning = !m_isRunning;
                    startGame(SinglePlayer);
                }
                /*else if (!m_isRunning && event.key.code == sf::Keyboard::M) {
                    startGame(MultiPlayer);
                }*/
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
    rwindow.clear(sf::Color::White);
    rwindow.setView(m_mainView);

    for (int i = 0; i < numParticles; i++) {
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
    for (int i = 0; i < numParticles; i++) {
        circles[i].setRadius(10);
        circles[i].setPointCount(30);
        circles[i].setFillColor(sf::Color::Black);
        circles[i].setOrigin(10, 10);

        int circle_x, circle_y;
        circle_x = rand() % 760 + 30;
        circle_y = rand() % 560 + 30;
        circles[i].setPosition(circle_x, circle_y);

        std::cout << "Circle " << i+1 << ": X: " << circle_x << "\tY: " << circle_y << std::endl;
    }
    std::cout << std::endl;
    m_isRunning = true;
}

sf::Vector2f Game::coordWorldToView(const tacoTruck::Vector2D coord) const {
    return sf::Vector2f(coord.x, -coord.y);
}

tacoTruck::Vector2D Game::coordViewToWorld(const sf::View & view, const sf::Vector2f & coord) {
    return tacoTruck::Vector2D();
}
