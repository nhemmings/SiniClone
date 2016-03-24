#include "physics/precision.hpp"

class GameObject {
private:
    real pos_X;
    real pos_Y;
    void* inputComp;
    void* physicsComp;
    void* graphicsComp;
protected:
	GameObject(void* input = NULL, void* physics = NULL, void* graphics = NULL) :
        inputComp(input), physicsComp(physics), graphicsComp(graphics) {}
public:
	virtual ~GameObject();
	virtual void write(sf::Packet& outPacket) = 0;
	virtual void read(sf::Packet& inPacket) = 0;
};
