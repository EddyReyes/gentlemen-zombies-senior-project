
#include "playerCharacter.h"


PlayerCharacter::PlayerCharacter()
{
	//Player life points is set to 100;
	playerHealth = 100;
	damageResistance = 0.50;
};
float PlayerCharacter::getHealth()
{
	return playerHealth;
}

void PlayerCharacter::setHealth(int hp)
{
	hp = playerHealth;
}

void PlayerCharacter::healthRegenerate(int healthPack)
{
	playerHealth =+ healthPack;
}

void  PlayerCharacter::playerDamage(int damage)
{
	playerHealth -= (1 - damageResistance) * damage;
	if(playerHealth < 0) playerHealth = 0;
	
}



