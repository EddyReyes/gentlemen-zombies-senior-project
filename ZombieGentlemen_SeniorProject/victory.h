#pragma once
#include "stuff.h"

class victory : public stuff
{
public:
	victory(void);
	~victory(void);
	void update(float timePassed);
	void animate();
};
