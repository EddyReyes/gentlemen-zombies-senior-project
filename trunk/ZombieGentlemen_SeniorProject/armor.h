#pragma once

//Armor class, handles player armor

class Armor
{
private:
	int armorType;
	float armorHealth;
	float damageResistance;
public:
	Armor();
	bool initPlayerArmor(int a_armorType);
	~Armor();
	void damageArmor(int damage);
	float armorRegenerate();
	bool armorDepleted(void);
	float getArmorHealth();
	float getDamageResistance();
	void setArmorHealth(float a_armorHealth);
	void setArmorType(int a_armorType);
	int getArmorType();
	void setDamageResistance(float a_damageResistance);
};