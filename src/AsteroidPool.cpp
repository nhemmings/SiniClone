#include "AsteroidPool.hpp"

AsteroidPool::AsteroidPool(const CoordAdapter & adapter) : m_CoordAdapter(adapter), m_activeIndex(0)
{
    m_Circles = new sf::CircleShape[s_maxAsteroids];
    m_Particles = new physics::Particle[s_maxAsteroids];
    m_Circles[0].setFillColor(sf::Color::White);
}

AsteroidPool::~AsteroidPool()
{
    delete [] m_Circles;
    delete [] m_Particles;
}

int AsteroidPool::addAsteroid(float radius, unsigned short pointCount, float mass, Vector2D pos, Vector2D vel) {
    if (m_activeIndex >= s_maxAsteroids)
        return -1;
    m_Circles[m_activeIndex].setRadius(radius);
    m_Circles[m_activeIndex].setPointCount(pointCount);
    m_Particles[m_activeIndex].setMass(mass);
    m_Particles[m_activeIndex].setPosition(pos);
    m_Particles[m_activeIndex].setVelocity(vel);
    return m_activeIndex++;
}

void AsteroidPool::updateAsteroids(const sf::Time & duration) {
    for (unsigned int i = 0; i < m_activeIndex; i++) {
        m_Particles[i].integrate(duration.asSeconds());
        sf::Vector2u convertedCoord = m_CoordAdapter.physToWindow(m_Particles[i].getPosition());
        m_Circles[i].setPosition(convertedCoord.x, convertedCoord.y);
    }

}

void AsteroidPool::renderAsteroids(sf::RenderWindow & rwindow) {
    for (unsigned int i = 0; i < m_activeIndex; i++)
        rwindow.draw(m_Circles[i]);
}

bool AsteroidPool::removeAsteroid(unsigned int ID) {
    if (ID >= m_activeIndex)            // Safeguard against IDs outside of the active pool
        return false;
    else if (ID == (m_activeIndex - 1)) // No need to swap if asteroid is already at the tail of the pool
    {
        m_activeIndex--;
        return true;
    }
    else                                // Swap the tail into the newly vacated index
    {
        m_activeIndex--;
        m_Circles[ID].setRadius(m_Circles[m_activeIndex].getRadius());
        m_Circles[m_activeIndex].setPointCount(m_Circles[m_activeIndex].getPointCount());
        m_Particles[m_activeIndex].setMass(m_Particles[m_activeIndex].getMass());
        m_Particles[m_activeIndex].setPosition(m_Particles[m_activeIndex].getPosition());
        m_Particles[m_activeIndex].setVelocity(m_Particles[m_activeIndex].getVelocity());
    }
    return true;
}
