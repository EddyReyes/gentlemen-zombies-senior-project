#pragma once
#include "stuff.h"

class key :public stuff
{
public:
	key(void);
	~key(void);
	void update(float updateTime);
	void animate();
};
