#pragma once
#include "dxManager.h"
#include "object.h"

class player
{
private:
	float playerHealth;
	float damageResistance;
	float money;
	object* m_char;
public:
	
	player();
	player(dxManager * a_dxMgr,char*file);

	object* getObj(){return m_char;}

	~player();
	float getHealth();
	void setHealth(float a_health);
	void healthRegenerate(float healthPack);
	void playerDamage(float damage);
	float getMoney();
	void addMoney(float recieve);
	void setMoney(float a_money);
	void Draw();
	void moveplayer(float,float);


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
