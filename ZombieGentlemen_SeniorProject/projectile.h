#pragma once
#include "entity.h"

enum projectileState{fire, hit};

class projectile : public entity
{
private:
projectileState state;

public:
	projectile();
	~projectile();
	void update();
};