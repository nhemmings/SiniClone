#ifndef ASTEROIDENTITY_HPP_
#define ASTEROIDENTITY_HPP_

#include "SFML/Graphics.hpp"
#include "physics/particle.hpp"
#include "CoordAdapter.hpp"

using physics::Vector2D;

class AsteroidEntity
{
private:
    sf::CircleShape m_Circle;
    physics::Particle m_Particle;
    CoordAdapter* m_CoordAdapter;
    AsteroidEntity();
public:
    AsteroidEntity(CoordAdapter* coordAdapter, float radius, unsigned short pointCount,
                   Vector2D position, Vector2D velocity);
    virtual ~AsteroidEntity();

    void update(float duration);
};

#endif // ASTEROIDENTITY_HPP_
