#include "playerCharacter.h"

PlayerCharacter::PlayerCharacter(dxManager * a_dxMgr, std::string filename)
{
	//Player life points is set to 100;
	playerHealth = 100;
	damageResistance = 0.50;
	playerImage = new XYPlane(a_dxMgr, filename);
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

void PlayerCharacter::setPlayerImage(std::string filename)
{
	playerImage->setImage(filename);
}

void PlayerCharacter::setPlayerSprite(int a_row, int a_column)
{
	playerImage->selectTextureSource(a_row, a_column);
}

void PlayerCharacter::initPlayerSpriteSheet(int a_rows, int a_columns)
{
	playerImage->setImageRowsColumns(a_rows, a_columns);
}

void PlayerCharacter::setPosition(float a_x, float a_y, float a_z)
{
	playerImage->setPosition( a_x,  a_y,  a_z);
}

void PlayerCharacter::Draw()
{
	playerImage->draw();
}