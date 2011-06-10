#pragma once
#include "stuff.h"

enum doorState{doorClosed, doorOpen};
class door :
	public stuff
{
private: doorState state;
public:
	door(void);
	~door(void);
	void update(float updateTime);
	void animate();

	void open();
	bool isOpen();
};
