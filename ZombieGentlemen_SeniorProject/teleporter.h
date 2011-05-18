#pragma once
#include "entity.h"


class teleporter:public entity
{
public:
	teleporter();
	~teleporter();
	void update(float timePassed);
	void animate();
private:
	object* to_port;//object being teleported
	float time;
	int animate_state;
};