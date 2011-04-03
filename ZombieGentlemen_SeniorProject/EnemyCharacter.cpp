#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(dxManager* a_dxMgr, std::string filename)
{
	enemyImage = new XYPlane(a_dxMgr, filename);
};
EnemyCharacter::~EnemyCharacter()
{
	enemyImage->~XYPlane();
};

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

void EnemyCharacter::setEnemieImage(std::string filename)
{
	// setting a image. 
	enemyImage->setImage(filename);
}

void EnemyCharacter::setEnemieSprite(int a_row, int a_column)
{
	// asking what image to show in the sprite. its asking what row and what column.
	enemyImage->selectTextureSource(a_row, a_column);
}

void EnemyCharacter::initEnemieSpriteSheet(int a_rows, int a_columns)
{
	// asking how many rows and how many columns dos the sprite has.
	enemyImage->setImageRowsColumns(a_rows, a_columns);
}

void EnemyCharacter::setPosition(float a_x, float a_y, float a_z)
{
	// askig where to place the image in the game world. 
	enemyImage->setPosition( a_x,  a_y,  a_z);
}

void EnemyCharacter::Draw()
{
	// calls the draw function to draw the image.
	enemyImage->draw();
}
XYPlane* EnemyCharacter::getimg()
{
	return enemyImage;
}