#pragma once
#include "object.h"

enum stuffType{none, checkpoint, armor, key, teleporter, door};
class stuff
{
	object * m_object;
	stuffType type;
	bool pickedUp;

public:
	stuff(void);
	~stuff(void);
	void setPosition(float x, float y);
	void crossed();
	bool isCrossed();
	void setObject(object * a_object);
	object * getObject();
};
