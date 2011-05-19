#pragma once
#include "object.h"

enum stuffType{stuff_none, stuff_checkpoint, stuff_armor, stuff_key, stuff_teleporter, stuff_door};
class stuff
{
protected:
	object * m_object;
	stuffType type;
	bool pickedUp;

public:
	stuff(void);
	~stuff(void);

	// virtual functions
	virtual void update(float) = 0;
	virtual void animate() = 0;
	
	// member functions
	void setPosition(float x, float y);
	void pickUp();
	bool isPickedUp();
	void setObject(object * a_object);
	int getType();

	// accessors
	object * getObject();
};
