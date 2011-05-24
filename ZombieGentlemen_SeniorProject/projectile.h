#pragma once
#include "entity.h"

enum projectileState{fire, hit};

class projectile : public entity
{
private:
float time;
projectileState state;
D3DXVECTOR3 * pos;

public:
	projectile();
	~projectile();
	void update(float timePassed);
	void returnTurret();
	void animate();
	void reset();
	void firing(float a_updateTime);
	/*Have three function that make the projectile move. */
	
};