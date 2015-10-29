#ifndef COORDADAPTER_HPP_
#define COORDADAPTER_HPP_

#include "SFML/System.hpp"
#include "physics/Vector2D.hpp"

using sf::Vector2u;
using physics::Vector2D;

/**
 *  Adapter class to convert between differing (2D) coordinate systems (e.g. those of physics and graphics
 *  subsystems).
 */
class CoordAdapter2D
{
private:
    /**< Default constructor, Copy constructor, and Assignment operator private to guard against their use. */
    CoordAdapter2D();
    CoordAdapter2D(const CoordAdapter2D& other);
    CoordAdapter2D& operator=(const CoordAdapter2D& other);
protected:
    /**< Graphics subsystem vector representation of the viewing window's dimensions. */
    sf::Vector2u m_WindowSize;
public:
    /**
     *  Constructs a basic CoordAdapter2D object.
     *
     *  @param windowSize the graphics subsystem's vector representation of the viewing window's size.
     */
    CoordAdapter2D(const Vector2u windowSize) : m_WindowSize(windowSize) {}

    /**
     *  Updates the CoordAdapter2D's window size information. Used to inform the CoordAdapter2D of changes to the
     *  dimensions of the rendering window associated with it.
     *
     *  @param windowSize the graphics subsystem's vector representation of the viewing window's current (updated) size.
     */
    void updateWindowSize(const sf::Vector2u& windowSize) { m_WindowSize = windowSize; }

    /**
     *  Converts the provided X-axis component from physics space to graphics space.
     */
    virtual float physToWindowX(const float x) const = 0;

    /**
     *  Converts the provided Y-axis component from physics space to graphics space.
     */
    virtual float physToWindowY(const float y) const = 0;

    /**
     *  Converts the provided vector from physics space to graphics space.
     */
    virtual Vector2u physToWindow(const Vector2D& vec) const = 0;

    /**
     *  Converts the provided X-axis component from graphics space to physics space.
     */
    virtual float windowToPhysX(const float x) const = 0;

    /**
     *  Converts the provided Y-axis component from graphics space to physics space.
     */
    virtual float windowToPhysY(const float y) const = 0;

    /**
     *  Converts the provided vector from graphics space to physics space.
     */
    virtual Vector2D windowToPhys(const Vector2u& vec) const = 0;
};

#endif // COORDADAPTER_HPP_
