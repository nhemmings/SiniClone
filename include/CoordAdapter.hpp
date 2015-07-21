#ifndef COORDADAPTER_HPP_
#define COORDADAPTER_HPP_

#include "SFML/System.hpp"
#include "physics/Vector2D.hpp"
#include "EntityManager.hpp"

using sf::Vector2u;
using physics::Vector2D;

class CoordAdapter
{
private:
    CoordAdapter();
    CoordAdapter(const CoordAdapter& other);
    CoordAdapter& operator=(const CoordAdapter& other);
protected:
    sf::Vector2u m_WindowSize;
public:
    CoordAdapter(const Vector2u windowSize) : m_WindowSize(windowSize) {}
    void updateWindowSize(const sf::Vector2u& windowSize) { m_WindowSize = windowSize; }

    virtual float physToWindowX(const float x) const = 0;
    virtual float physToWindowY(const float y) const = 0;
    virtual Vector2u physToWindow(const Vector2D& vec) const = 0;

    virtual float windowToPhysX(const float x) const = 0;
    virtual float windowToPhysY(const float y) const = 0;
    virtual Vector2D windowToPhys(const Vector2u& vec) const = 0;
};

#endif // COORDADAPTER_HPP_
