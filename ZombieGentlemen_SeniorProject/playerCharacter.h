#pragma once
#include "dxManager.h"
#include "hudImage.h"
#include "XYPlane.h"
#include "collisionRect.h"

class PlayerCharacter
{
private:
	float playerHealth;
	float damageResistance;
	float money;
	XYPlane * playerImage;
	collisionRect *c;
public:
	
	PlayerCharacter(dxManager* a_dxMgr, std::string filename);
	PlayerCharacter();
	~PlayerCharacter();
	float getHealth();
	void setHealth(int );
	void healthRegenerate(int healthPack);
	void playerDamage(int damage);
	float getMoney();
	void addMoney(float recieve);
	void setMoney(int a_money);

	void setPlayerImage(std::string filename);
	void setPlayerSprite(int a_row, int a_column);
	void initPlayerSpriteSheet(int a_rows, int a_columns);
	void setPosition(float a_x, float a_y, float a_z);
	void Draw();

	//unit test params
	XYPlane* getimg();
	float getHeight(){return playerImage->getHeight();}
	float getWidth(){return playerImage->getWidth();}
	D3DXVECTOR3 getPosition(){return *(playerImage->getPosition());}

	collisionRect* getcollisionbox(){return c;}
	//void attack(int & weapon );
	//void defend();
	//addItem()
	//removeItem()
	//addMoney()
	//removeMoney()
	//updateHelmet()
	//updateArmor()
	//void calculateDamageResistance()
	//calculateMovementSpeed()
	//calculateMaxJumpHeight()

};
