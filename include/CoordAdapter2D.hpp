#ifndef COORDADAPTER_HPP_
#define COORDADAPTER_HPP_

#include "SFML/System.hpp"
#include "physics/Vector2D.hpp"

using sf::Vector2u;
using physics::Vector2D;
/**
 *  Adapter class to convert between the differing (2D) coordinate systems of the physics and graphics engines.
 */
class CoordAdapter2D
{
private:
    CoordAdapter2D();
    CoordAdapter2D(const CoordAdapter2D& other);
    CoordAdapter2D& operator=(const CoordAdapter2D& other);
protected:
    sf::Vector2u m_WindowSize;
public:
    CoordAdapter2D(const Vector2u windowSize) : m_WindowSize(windowSize) {}
    void updateWindowSize(const sf::Vector2u& windowSize) { m_WindowSize = windowSize; }

    virtual float physToWindowX(const float x) const = 0;
    virtual float physToWindowY(const float y) const = 0;
    virtual Vector2u physToWindow(const Vector2D& vec) const = 0;

    virtual float windowToPhysX(const float x) const = 0;
    virtual float windowToPhysY(const float y) const = 0;
    virtual Vector2D windowToPhys(const Vector2u& vec) const = 0;
};

#endif // COORDADAPTER_HPP_
