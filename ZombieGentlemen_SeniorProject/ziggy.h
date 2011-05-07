#pragma once
#include "entity.h"
#include "dxManager.h"

class ziggy: public entity
{
private:
	D3DXVECTOR3	* pos;
public:
	void load();
	void update();
};