#pragma once
#include "entity.h"
#include "dxManager.h"

class ziggy: public entity
{
private:
	D3DXVECTOR3	* pos;

	// THIS IS NEW DATA, ITS NOT PART OF THE DESIGN
	spriteMovement ziggyMovement;
public:
	void yMovement();
	void load();
	void update();
};