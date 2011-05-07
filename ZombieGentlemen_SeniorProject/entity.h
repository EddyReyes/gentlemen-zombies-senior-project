#pragma once
#include "object.h"

class entity
{
protected:
	object * m_object;
	bool alive, armor;
	// entity will also require a state


public:
	// constructor destructor
	entity();
	~entity();

	// member functions
	void animate();
	
	//virtual functions (for child classes)
	virtual void update() = 0;

	// mutators
	void setObject(object * a_object);
	void entityDead();
	void entityAlive();

	//accessors
	object * getObject();
	bool isAlive();
	bool hasArmor();
};