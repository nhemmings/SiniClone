#include "EntityManager.hpp"

//**********************************************************************************************************************
//  Constructors
//**********************************************************************************************************************
EntityManager::EntityManager(sf::Window& window) :  m_Window(window),
                                                    m_CoordAdapter(window.getSize()),
                                                    m_nextID(0)
{
    //ctor
}

EntityManager::~EntityManager()
{
    //dtor
}

//**********************************************************************************************************************
//  SFMLCoordAdapter Methods
//**********************************************************************************************************************
inline float EntityManager::SFMLCoordAdapter::physToWindowX(const float x) const {
    return x;
}

inline float EntityManager::SFMLCoordAdapter::physToWindowY(const float y) const {
    return (m_WindowSize.y - y);
}

inline Vector2u EntityManager::SFMLCoordAdapter::physToWindow(const Vector2D& vec) const {
    return Vector2u(vec.x, vec.y);
}

inline float EntityManager::SFMLCoordAdapter::windowToPhysX(const float x) const {
    return x;
}

inline float EntityManager::SFMLCoordAdapter::windowToPhysY(const float y) const {
    return (m_WindowSize.y - y);
}

inline Vector2D EntityManager::SFMLCoordAdapter::windowToPhys(const Vector2u& vec) const {
    return Vector2D(vec.x, vec.y);
}

//**********************************************************************************************************************
//  EntityManager Methods
//**********************************************************************************************************************
int EntityManager::getNextID() {
    return m_nextID++;
}

void EntityManager::update(float duration) {
    m_CoordAdapter.updateWindowSize(m_Window.getSize());
}
