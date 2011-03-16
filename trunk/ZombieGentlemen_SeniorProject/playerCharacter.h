#pragma once
class Player_Ch
{
private:
	int health;
	int damageResistance;
public:
	
	Player_Ch();
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