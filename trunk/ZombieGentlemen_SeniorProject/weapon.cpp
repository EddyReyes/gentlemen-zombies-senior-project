#include "weapon.h"

Weapon::Weapon()
{
	//damage points will always be set to zero. 
	damage = 0;
};

int Weapon::shovle()
{
	// the shovle only have 5 attack points. basicly it can only fight weak enemies.
	int hitPoints = 5;
	damage = hitPoints;
	return damage;
};