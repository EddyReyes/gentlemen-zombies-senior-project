#pragma once
#include "entity.h"
#include "dxManager.h"

class ziggy: public entity
{
private:
	D3DXVECTOR3	* pos;
	spriteMovement ziggyMovement;
public:
	void yMovement();
	void load();
	void update();
};