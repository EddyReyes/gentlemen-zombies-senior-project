#include "playerCharacter.h"

PlayerCharacter::PlayerCharacter(dxManager * a_dxMgr, std::string filename)
{
	//Player life points is set to 100;
	//Players damage resistance is at 50%
	playerHealth = 100;
	damageResistance = 0.50;
	playerImage = new XYPlane(a_dxMgr, filename);
	c = new collisionRect;
	c->initRect(playerImage);
	c->update();
};
PlayerCharacter::~PlayerCharacter()
{
	playerImage->~XYPlane();
	c->~collisionRect();
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
	playerHealth =+ healthPack;
}

void  PlayerCharacter::playerDamage(int damage)
{
	//udateing the players current health: health is being depleated. 
	playerHealth -= (1 - damageResistance) * damage;
	if(playerHealth < 0) playerHealth = 0;
	// if health equals zero then the player is dead and the health will print out zero for remaining health.
	
}

void PlayerCharacter::setPlayerImage(std::string filename)
{
	// setting a image. 
	playerImage->setImage(filename);
}

void PlayerCharacter::setPlayerSprite(int a_row, int a_column)
{
	// asking what image to show in the sprite. its asking what row and what column.
	playerImage->selectTextureSource(a_row, a_column);
}

void PlayerCharacter::initPlayerSpriteSheet(int a_rows, int a_columns)
{
	// asking how many rows and how many columns dos the sprite has.
	playerImage->setImageRowsColumns(a_rows, a_columns);
}

void PlayerCharacter::setPosition(float a_x, float a_y, float a_z)
{
	// askig where to place the image in the game world. 
	playerImage->setPosition( a_x,  a_y,  a_z);
	c->initRect(playerImage);
	c->update();
}

void PlayerCharacter::Draw()
{
	// calls the draw function to draw the image.
	playerImage->draw();
}
XYPlane* PlayerCharacter::getimg()
{
	return playerImage;
}