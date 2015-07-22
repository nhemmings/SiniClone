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

    EntityManager();    // default ctor hidden to enforce dependency injection!
    EntityManager(const EntityManager& other);  // 'Singleton' -- Do not allow copy construction.
    EntityManager& operator=(const EntityManager& other);   // 'Singleton' -- Do not allow assignment.

    void updateWindowSize(const sf::Vector2u& windowSize);
public:
    EntityManager(sf::Window& window);
    ~EntityManager();
    int getNextID();
    void registerEntity(BaseGameEntity* newEntity);
    BaseGameEntity* getEntityFromID(int ID) const;
    void removeEntity(BaseGameEntity* pEntity);
    void removeEntityByID(int ID);
protected:
};

#endif // ENTITYMANAGER_HPP_
