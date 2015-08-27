#ifndef ASTEROIDPOOL_HPP
#define ASTEROIDPOOL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "physics/Vector2D.hpp"
#include "physics/particle.hpp"
#include "CoordAdapter.hpp"

class AsteroidPool
{
private:
    static const unsigned s_maxAsteroids = 25;
    sf::CircleShape* m_Circles;
    physics::Particle* m_Particles;
    const CoordAdapter & m_CoordAdapter;
    unsigned m_activeIndex;
public:
    explicit AsteroidPool(const CoordAdapter & adapter);
    virtual ~AsteroidPool();

    int addAsteroid(float radius, unsigned short pointCount, float mass, Vector2D pos, Vector2D vel);
    void updateAsteroids(const sf::Time & duration);
    void renderAsteroids(sf::RenderWindow & rwindow);
private:
    bool removeAsteroid(unsigned int ID);
};

#endif // ASTEROIDPOOL_HPP
