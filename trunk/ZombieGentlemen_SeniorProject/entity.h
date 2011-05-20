#pragma once
#include "object.h"
#include "imageManager.h"


enum entityType{none, entityPlayer, entityTurret, entityGoomba, entityZiggy, entityObstacle, entityTroll};
class entity
{
protected:
	object * m_object;
	entityType type;
	bool alive, armor;
	D3DXVECTOR3 defaultPos;
	// entitys will also require a state

public:
	// constructor destructor
	entity();
	~entity();

	//virtual functions (for child classes)
	virtual void update(float) = 0;
	virtual void animate() = 0;
	virtual void reset() = 0;
	
	// member functions
	void setPosition(float x, float y);
	void setPosition(D3DXVECTOR3);
	void setDefaultPos(D3DXVECTOR3 * pos);
	void setDefaultPos(float x, float y);
	void moveToDefaultPos();

	// mutators
	void setObject(object * a_object);
	void entityDead();
	void entityAlive();

	//accessors
	object * getObject();
	bool isAlive();
	bool hasArmor();
	int getType();
};