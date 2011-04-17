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
public:
	
	PlayerCharacter();
	~PlayerCharacter();
	float getHealth();
	void setHealth(int );
	void healthRegenerate(int healthPack);
	void playerDamage(int damage);
	float getMoney();
	void addMoney(float recieve);
	void setMoney(int a_money);
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
