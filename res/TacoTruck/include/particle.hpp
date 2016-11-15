#ifndef PHYSICS_PARTICLE_HPP_
#define PHYSICS_PARTICLE_HPP_
/*
 * A Particle is the simplest object that can be simulated in the physics system. It is essentially a point mass with
 * position data, but no orientation (heading). It can be integrated forward through time, and it can have linear
 * forces and impulses applied to it.
 *
 * Author: Nathan Hemmings
 *
 * Date created: 07/06/2015
 *
 */
#include "Vector2D.hpp"

namespace tacoTruck {
class Particle {
protected:
    real inverseMass;
    real damping;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D forceAccum;
public:
    /** Creates a new Particle with default parameters. */
    Particle();

    /**
     *	Integrates the particle forward in time by the given amount.
     *	This function uses a Newton-Euler integration method, which is a linear approximation
     *	to the correct integral. For this reason it may be inaccurate in some cases.
     *
     *  @param duration the amount of time (in seconds) to simulate during this integration step
     */
    void integrate(real duration);

    /**
     *	Sets the mass of the particle.
     *
     * @param mass The new mass of the body. This may not be zero. Small masses can produce unstable rigid bodies
     *
     */
    void setMass(const real mass);
    real getMass() const;
    void setInverseMass(const real inverseMass);
    real getInverseMass() const;
    void setDamping(const real damping);
    real getDamping() const;
    void setPosition(const Vector2D& position);
    void setPosition(const real x, const real y);
    void getPosition(Vector2D* position) const;
    Vector2D getPosition() const;
    void setVelocity(const Vector2D& velocity);
    void setVelocity(const real x, const real y);
    void getVelocity(Vector2D* velocity) const;
    Vector2D getVelocity() const;
    void setAcceleration(const Vector2D& acceleration);
    void setAcceleration(const real x, const real y);
    void getAcceleration(Vector2D* acceleration) const;
    Vector2D getAcceleration() const;

    /** Returns true if the mass of the particle is NOT infinite. */
    bool hasFiniteMass() const;

    /**
     *  Clears the forces applied to the particle. This will be called automatically after each integration step.
     */
    void clearAccumulator();

    /**
     *  Adds the given force to the particle (to be applied at the next iteration only).
     *
     *  @param force a force to be applied to this particle at the next integration step
     */
    void addForce(const Vector2D& force);
};	// Particle
}	// namespace tacoTruck

 #endif	// PHYSICS_PARTICLE_HPP_
