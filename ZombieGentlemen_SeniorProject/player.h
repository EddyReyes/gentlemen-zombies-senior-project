#pragma once
#include "dxManager.h"
#include "object.h"

class Player
{
private:
	float PlayerHealth;
	float damageResistance;
	float money;
	object* m_char;
public:
	
	Player();
	Player(dxManager * a_dxMgr,char*file);

	object* getObj(){return m_char;}

	~Player();
	float getHealth();
	void setHealth(float a_health);
	void healthRegenerate(float healthPack);
	void PlayerDamage(float damage);
	float getMoney();
	void addMoney(float recieve);
	void setMoney(float a_money);
	void Draw();
	void movePlayer(float,float);


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
