
#include "playerCharacter.h"


Player_Ch::Player_Ch()
{
	//Player life points is set to 100;
	health = 100;
};
int Player_Ch::getHealth()
{
	// Geting players life points
	return health;
};
void Player_Ch::setHealth(int hp)
{
	// Setting players life.
	health = hp;
};

void Player_Ch::attack(int &enemie, int weapon )
{
	int remainHealth;
	
	/*Depending on what enemie and what weapon the players is using. 
	If the player is fighting a weak enemie and his life points is 15 and 
	the player has a shovle as weapon whitch will be 5 attack points. */
	remainHealth = enemie - weapon;
	enemie = remainHealth;
	
};

void Player_Ch::defend()
{
	
};

void Player_Ch::takeDamage()
{
	
};


