#include "UserInterface.h"

UserInterface::UserInterface()
{
	character = NULL;
	enemyCharacter = NULL;
	hudElement = NULL;
}
UserInterface::~UserInterface()
{
	if(character)
	character->~PlayerCharacter();
	if(enemyCharacter)
	enemyCharacter->~EnemyCharacter();
	if(hudElement)
	hudElement->~HUD();
}
bool UserInterface::playerEngagesEnemy()
{
	//check if player collides with enemy

	return true;
}
bool UserInterface::playerChecksHealth()
{
	return true;
}
bool UserInterface::playerChecksArmor()
{
	return true;
}
void UserInterface::playerAttacks()
{
	
}
void UserInterface::playerAttacked()
{
	hudElement->updateHealthBarDamage();
}
void UserInterface::playerDied()
{

}
void UserInterface::enemyDied()
{

}
void UserInterface::EnemyDropsCoin()
{

}
void UserInterface::playerCurrencyRecieved()
{

}
void UserInterface::updatePlayerCurrency()
{

}