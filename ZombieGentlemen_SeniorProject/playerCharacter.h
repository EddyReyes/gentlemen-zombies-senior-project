#pragma once
class PlayerCharacter
{
private:
	int health;
	int damageResistance;
public:
	
	PlayerCharacter();
	int getHealth();
	void setHealth(int );
	void attack(int & , int );
	void defend();
	void takeDamage();
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