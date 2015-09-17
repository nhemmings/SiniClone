#include "AsteroidEntity.hpp"

AsteroidEntity::AsteroidEntity(CoordAdapter2D* coordAdapter, float radius, unsigned short pointCount, float mass,
                               Vector2D position, Vector2D velocity)
    : m_Circle(radius, pointCount),
      m_CoordAdapter(coordAdapter)
{
    m_Particle.setPosition(position);
    m_Particle.setVelocity(velocity);
}

AsteroidEntity::~AsteroidEntity()
{
    //dtor
}

void AsteroidEntity::update(float duration) {
    m_Particle.integrate(duration);
}
