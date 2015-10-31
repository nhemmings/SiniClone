#ifndef ASTEROIDENTITY_HPP_
#define ASTEROIDENTITY_HPP_

#include "SFML/Graphics.hpp"
#include "physics/particle.hpp"
#include "CoordAdapter2D.hpp"

using physics::Vector2D;

class AsteroidEntity
{
private:
    sf::CircleShape m_Circle;
    physics::Particle m_Particle;
    CoordAdapter2D* m_CoordAdapter;
    bool isActive;
public:
    AsteroidEntity() : isActive(false) {}
    AsteroidEntity(CoordAdapter2D* coordAdapter, float radius, unsigned short pointCount, float mass,
                   Vector2D position, Vector2D velocity);
    virtual ~AsteroidEntity();

    void update(float duration);
};

#endif // ASTEROIDENTITY_HPP_
