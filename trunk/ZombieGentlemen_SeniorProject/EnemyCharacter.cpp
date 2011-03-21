#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter()
{
	health = 100;
};

int EnemyCharacter::getEasyenemie()
{
	// the  weak enemie only has 15 life points.

	return health;
};

void EnemyCharacter::setEasyenemie(int hp)
{
	///setting the enemies life. 
	health = hp;
};