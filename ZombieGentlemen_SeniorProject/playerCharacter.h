#pragma once
#include "dxManager.h"
#include "object.h"

class PlayerCharacter
{
private:
	float playerHealth;
	float damageResistance;
	float money;
	object* m_char;
public:
	
	PlayerCharacter();
	PlayerCharacter(dxManager * a_dxMgr,char*file);

	object* getObj(){return m_char;}

	~PlayerCharacter();
	float getHealth();
	void setHealth(int );
	void healthRegenerate(int healthPack);
	void playerDamage(int damage);
	float getMoney();
	void addMoney(float recieve);
	void setMoney(int a_money);
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
