#pragma once
#include "entity.h"

enum projectileState{fire, hit};

class projectile : public entity
{
private:
projectileState state;
float time;
D3DXVECTOR3 pos;

public:
	projectile();
	~projectile();
	void update(float timePassed);
	void returnTurret();
	void animate();
	/*Have three function that make the projectile move. */
	
};