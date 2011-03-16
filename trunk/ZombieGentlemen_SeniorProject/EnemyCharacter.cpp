#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter()
{
	health = 0;
};

int EnemyCharacter::getEasyenemie()
{
	// the  weak enemie only has 15 life points.
	int life = 15;
	health = life;

	return health;
};

void EnemyCharacter::setEasyenemie(int hp)
{
	///setting the enemies life. 
	health = hp;
};