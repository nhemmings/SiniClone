#include "AsteroidPool.hpp"

AsteroidPool::AsteroidPool(const CoordAdapter & adapter) : m_CoordAdapter(adapter), m_activeIndex(0)
{
    m_Circles = new sf::CircleShape[s_maxAsteroids];
    m_Particles = new physics::Particle[s_maxAsteroids];
}

AsteroidPool::~AsteroidPool()
{
    delete [] m_Circles;
    delete [] m_Particles;
}
