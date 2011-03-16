
#include "playerCharacter.h"


PlayerCharacter::PlayerCharacter()
{
	//Player life points is set to 100;
	health = 100;
	damage = 25;
};
int PlayerCharacter::getHealth()
{
	// Geting players life points
	return health;
};
void PlayerCharacter::setHealth(int a_health)
{
	// Setting players life.
	health = a_health;
};

void PlayerCharacter::attack(int &enemie, int weapon)
{
	int remainHealth;
	
	/*Depending on what enemie and what weapon the players is using. 
	If the player is fighting a weak enemie and his life points is 15 and 
	the player has a shovle as weapon whitch will be 5 attack points. */
	remainHealth = enemie - weapon;
	enemie = remainHealth;
	
};

void PlayerCharacter::defend()
{
	
};

int PlayerCharacter::takeDamage()
{
	health - damage;
	return health;
};


