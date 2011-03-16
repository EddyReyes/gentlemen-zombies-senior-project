#pragma once
class PlayerCharacter
{
private:
	int health;
	int damageResistance;
	int damage;
public:
	
	PlayerCharacter();
	int getHealth();
	void setHealth(int );
	void attack(int & , int );
	void defend();
	int takeDamage();
	//addItem()
	//removeItem()
	//addMoney()
	//removeMoney()
	//updateHelmet()
	//updateArmor()
	//calculateDamageResistance()
	//calculateMovementSpeed()
	//calculateMaxJumpHeight()
};