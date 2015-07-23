#include "AsteroidEntity.hpp"

AsteroidEntity::AsteroidEntity(CoordAdapter* coordAdapter, float radius, unsigned short pointCount,
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

void AsteroidEntity::update(flaot duration) {

}
