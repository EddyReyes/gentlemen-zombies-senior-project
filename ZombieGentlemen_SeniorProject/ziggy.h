#pragma once
#include "entity.h"

enum ziggyStates {fly1, fly2, fly3};

class ziggy: public entity
{
private:
	ziggyStates state;
	float time;
public:
	ziggy();
	~ziggy();
	void update(float timePassed);
	void animate();
	void reset();
};