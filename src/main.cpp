#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "EntityManager.hpp"

void runServerFrame(const sf::Time & dt);
void runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow);

class dtAverage {
private:
    static const unsigned short dtHistorySize = 10;
    sf::Time dtSMA;
    sf::Time dtHistory[dtHistorySize];
    unsigned short idx;
public:
    dtAverage(const sf::Time & dtIdeal);
    sf::Time update(sf::Time & dtCurrent);
};

int main()
{
    using sf::Clock;
    using sf::Time;

    static const Time s_tServerFrame = sf::seconds(1.0f/20.0f);
    static const Time s_dtIdeal = sf::seconds(1.0f/30.0f);
    sf::RenderWindow window(sf::VideoMode(500, 300), "SFML works!");
    EntityManager gameEntityManager(window);

    /* Initialize clocks */
    Time dtReal = s_dtIdeal;        // The real frame delta time, initialized to ideal value
    dtAverage m_dtAvg(s_dtIdeal);
    Time dtServer = sf::Time::Zero; // Delta time since last server frame
    Clock realTimeClock;
    Time tBegin = realTimeClock.getElapsedTime();

    // MAIN GAME LOOP
    while (window.isOpen())
    {
        // System message pump
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Server update
        dtServer += dtReal;
        if (dtServer >= s_tServerFrame) {
            runServerFrame(dtServer);
            dtServer -= s_tServerFrame;
        }

        // Client update
        runClientFrame(dtReal, window);

        // Timer update
        Time tEnd = realTimeClock.getElapsedTime();
        Time dtThisFrame = tEnd - tBegin;
        dtReal = m_dtAvg.update(dtThisFrame);
        tBegin = tEnd;
    }

    return 0;
}

void runServerFrame(const sf::Time & dt) {

}

void runClientFrame(const sf::Time & dt, sf::RenderWindow & rwindow) {
    rwindow.clear();
    rwindow.display();
}

dtAverage::dtAverage(const sf::Time & dtIdeal) : dtSMA(dtIdeal), idx(0) {
    for (int i = 0; i < dtHistorySize; i++) {
        dtHistory[i] = dtIdeal;
    }
}

sf::Time dtAverage::update(sf::Time & dtCurrent) {
    dtSMA = dtSMA + dtCurrent/float(dtHistorySize) - dtHistory[idx]/float(dtHistorySize);
    dtHistory[idx] = dtCurrent;
    idx = (idx + 1) % dtHistorySize;
    return dtSMA;
}
