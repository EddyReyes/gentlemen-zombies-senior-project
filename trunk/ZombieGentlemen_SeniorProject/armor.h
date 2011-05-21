#pragma once
#include "stuff.h"

class armor: public stuff
{
public:
	armor(void);
	~armor(void);
	void update(float timePassed);
	void animate();
};
