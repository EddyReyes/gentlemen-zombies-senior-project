#include "playerCharacter.h"


PlayerCharacter::PlayerCharacter()
{
	//Player life points is set to 100;
	//Players damage resistance is at 50%
	playerHealth = 100.0;
	damageResistance = 0.50;
	money = 0;
}
PlayerCharacter::~PlayerCharacter()
{
}
float PlayerCharacter::getHealth()
{
	//getting the players health.
	return playerHealth;
}

void PlayerCharacter::setHealth(int hp)
{
	// setting the players health
	hp = playerHealth;
}

void PlayerCharacter::healthRegenerate(int healthPack)
{
	//updateing players health.(When player receave a health pack it will add more life poits to player health.)
	playerHealth += healthPack;
}

void  PlayerCharacter::playerDamage(int damage)
{
	//udateing the players current health: health is being depleated. 
	playerHealth -= (1 - damageResistance) * damage;
	if(playerHealth < 0) playerHealth = 0;
	// if health equals zero then the player is dead and the health will print out zero for remaining health.
}

float PlayerCharacter::getMoney()
{
	return money;
}

void PlayerCharacter::addMoney(float recieve)
{
	float maxMoney = 50;
	money += recieve;
	if(money > maxMoney)
	money = maxMoney;
}

void PlayerCharacter::setMoney(int a_money)
{
	a_money = money;
}

void PlayerCharacter::Draw()
{

}
