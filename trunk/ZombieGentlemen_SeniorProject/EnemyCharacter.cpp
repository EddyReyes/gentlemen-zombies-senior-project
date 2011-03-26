#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(){};
EnemyCharacter::~EnemyCharacter(){};

bool EnemyCharacter::initEnemie(int a_enemieType)
{
	if(a_enemieType < 1 || a_enemieType > 3) return false;
	enemieHealth = 100;
	setEnemieType( a_enemieType);
	return true;
}


float EnemyCharacter::getEnemieHealth()
{
	return enemieHealth;
}

void EnemyCharacter::setEnemieHealth(int enemie_hp)
{
	enemie_hp = enemieHealth;
}
void EnemyCharacter::Enemiedamage(int damage)
{
	enemieHealth -= (1 - damageResistance) * damage;
	if(enemieHealth <= 0) enemieHealth = 0;
}

void EnemyCharacter::setEnemieType(int a_enemieType)
{
	enemieType  = a_enemieType ;
	damageResistance = 0.25 * enemieType;
}