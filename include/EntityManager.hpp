#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_
/**
 *  The EntityManager class owns and maintains the object pool for all game Entities, manages the lifetime and
 *  update cycle of all Entities, and provides any necessary conversions between the physics and graphics engines.
 */
#include "SFML/Graphics.hpp"
#include "CoordAdapter.hpp"
#include "BaseGameEntity.hpp"

using sf::Window;

class EntityManager
{
private:
    /**
     *  Adapter class to convert between the differing coordinate systems of the physics and graphics engines.
     *  Specifically, SFML puts the origin in the top left corner of the window and the Y-axis increases down. The
     *  physics engine puts the origin in the lower left and the Y-axis increases upward, which is more intuitive for
     *  physics simulation (i.e. gravity). This class provides helper functions to convert from one to the other.
     */
    class SFMLCoordAdapter : public CoordAdapter {
    public:
        SFMLCoordAdapter(const Vector2u windowSize) : CoordAdapter(windowSize) {}
        float physToWindowX(const float x) const;
        float physToWindowY(const float y) const;
        Vector2u physToWindow(const Vector2D& vec) const;

        float windowToPhysX(const float x) const;
        float windowToPhysY(const float y) const;
        Vector2D windowToPhys(const Vector2u& vec) const;
    };

    Window& m_Window;
    SFMLCoordAdapter m_CoordAdapter;
    int m_nextID;
    const static unsigned short maxEntities = 50;


    EntityManager();    // default ctor hidden to enforce dependency injection!
    EntityManager(const EntityManager& other);  // 'Singleton' -- Do not allow copy construction.
    EntityManager& operator=(const EntityManager& other);   // 'Singleton' -- Do not allow assignment.

public:
    EntityManager(sf::Window& window);
    ~EntityManager();
    int getNextID();
    void update(float duration);
protected:
};

#endif // ENTITYMANAGER_HPP_
