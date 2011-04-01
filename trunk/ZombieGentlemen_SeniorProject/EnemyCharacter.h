#pragma once
#include "dxManager.h"
#include "hudImage.h"
#include "XYPlane.h"
class EnemyCharacter
{
private:

	float enemieHealth;
	float damageResistance;
	int enemieType;
	XYPlane * enemyImage;

public:
	EnemyCharacter(dxManager* a_dxMgr, std::string filename);
	~EnemyCharacter();
	float getEnemieHealth();
	void setEnemieHealth(int);
	int getEnemieType();
	void setEnemieType(int a_armorType);
	bool initEnemie(int a_enmeieType);
	void Enemiedamage(int damage);

	void setEnemieImage(std::string filename);
	void setEnemieSprite(int a_row, int a_column);
	void initEnemieSpriteSheet(int a_rows, int a_columns);
	void setPosition(float a_x, float a_y, float a_z);
	void Draw();

};