#pragma once
#include "entity.h"

enum projectielsState{fire, hit};

class Projectiels : public entity
{
private:
projectielsState state;

public:
	Projectiels();
	~Projectiels();
	void update();
};