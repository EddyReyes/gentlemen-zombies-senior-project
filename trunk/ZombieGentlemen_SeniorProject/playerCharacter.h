#pragma once
#include "dxManager.h"
#include "hudImage.h"
#include "XYPlane.h"
class PlayerCharacter
{
private:
	float playerHealth;
	float damageResistance;
	XYPlane * playerImage;

public:
	
	PlayerCharacter(dxManager* a_dxMgr, std::string filename);
	~PlayerCharacter();
	float getHealth();
	void setHealth(int );
	void healthRegenerate(int  );
	void playerDamage(int damage);
	void setPlayerImage(std::string filename);
	void setPlayerSprite(int a_row, int a_column);
	void initPlayerSpriteSheet(int a_rows, int a_columns);
	void setPosition(float a_x, float a_y, float a_z);
	void Draw();

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
