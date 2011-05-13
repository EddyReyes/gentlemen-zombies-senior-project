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
	/*Have three function that make the projectile move. */
	
};