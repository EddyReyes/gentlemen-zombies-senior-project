#pragma once
#include "entity.h"

enum ziggyStates {fly1, fly2, fly3, deadZiggy};

class ziggy: public entity
{
private:
	ziggyStates state;
public:
	void load();
	void update(float timePassed);
};