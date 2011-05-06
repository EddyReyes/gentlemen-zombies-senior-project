#pragma once
#include "dxManager.h"
#include "object.h"
#include "armor.h"
#include "weapon.h"

class Player
{
private:
	float health;
	float damageResistance;
	float money;
	Armor * amr;
	weapon * plrWeapon;
	object* m_object;

public:
	
	Player();
	void init(object * a_object);

	object * getObject(){return m_object;}

	~Player();
	
	void setHealth(float a_health);
	void healthRegenerate(float healthPack);
	void damage(float damage);
	void addMoney(float recieve);
	void setMoney(float a_money);
	float getHealth();
	float getMoney();
	Armor * getArmor(){return amr;}
};
