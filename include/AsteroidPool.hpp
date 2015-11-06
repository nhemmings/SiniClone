#ifndef ASTEROIDPOOL_HPP
#define ASTEROIDPOOL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "physics/Vector2D.hpp"
#include "physics/particle.hpp"
#include "CoordAdapter2D.hpp"

/**
 *  Management pool for asteroid entities. Manages memory for both physics particles and shape sprites.
 */
class AsteroidPool
{
private:
    const unsigned m_maxAsteroids = 25;         /**< Maximum number of asteroids allowed in the pool. */
    sf::CircleShape* m_Circles;                 /**< Pointer to array of asteroid sprites. */
    physics::Particle* m_Particles;             /**< Pointer to array of asteroid particles. */
    const CoordAdapter2D & m_CoordAdapter;      /**< Adapter to convert between physics and graphics coord systems */
    unsigned m_activeIndex;                     /**< The next open index for asteroid insertion. */
public:
    /**
     *  Constructs a basic AsteroidPool with the given CoordAdapter2D.
     */
    explicit AsteroidPool(const CoordAdapter2D & adapter, unsigned maxAsteroids);
    virtual ~AsteroidPool();

    /**
     *  Creates a new asteroid in the pool, initializing it with the provided parameters (provided the pool is not
     *  full).
     *
     *  @param radius the radius of the new asteroid's sprite
     *  @param pointCount the pointCount of the new asteroid's sprite
     *  @param mass the mass of the new asteroid's particle
     *  @param damping the damping factor of the new asteroid's particle
     *  @param pos the initial positional vector of the new asteroid's particle
     *  @param vel the initial velocity vector of the new asteroid's particle
     *  @param accel the initial acceleration vector of the new asteroid's particle
     *
     *  @return -1 if the add request failed, otherwise the number of active asteroids (including the newly added one).
     */
    int addAsteroid(float radius, unsigned short pointCount, float mass, float damping,
                    Vector2D pos, Vector2D vel, Vector2D accel);

    /**
     *  Eliminate the designated asteroid from the pool of active asteroids.
     *
     *  @param ID the pool index of the asteroid to be removed
     */
    bool removeAsteroid(unsigned int ID);

    /**
     *  Advance asteroids forward one simulation frame.
     *
     *  @param duration the elapsed time associated with the current frame
     */
    void updateAsteroids(const sf::Time & duration);

    /**
     *  Render all active asteroids to the provided render target.
     *
     *  @param rwindow the RenderWindow to render the asteroids to
     */
    void renderAsteroids(sf::RenderWindow & rwindow);
};

#endif // ASTEROIDPOOL_HPP
