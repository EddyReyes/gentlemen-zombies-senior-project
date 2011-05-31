#pragma once
#include "stuff.h"

class armor: public stuff
{
public:
	armor();
	~armor(void);
	void update(float timePassed);
	void animate();
};
