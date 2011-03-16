#include "EnemieCharacter.h"

Enemie_Ch::Enemie_Ch()
{
	health = 0;
};

int Enemie_Ch::getEasyenemie()
{
	// the  weak enemie only has 15 life points.
	int life = 15;
	health = life;

	return health;
};

void Enemie_Ch::setEasyenemie(int hp)
{
	///setting the enemies life. 
	health = hp;
};