#pragma once
class PlayerCharacter
{
private:
	float playerHealth;
	float damageResistance;

public:
	
	PlayerCharacter();
	float getHealth();
	void setHealth(int );
	void healthRegenerate(int  );
	void playerDamage(int damage);

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
