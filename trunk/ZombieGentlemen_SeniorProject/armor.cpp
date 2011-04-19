#include "armor.h"

Armor::Armor()
{
		armorHealth = 80.0;//armor health
}
bool Armor::initPlayerArmor(int a_armorType)
{
	if (a_armorType < 1 || a_armorType > 3) return false;
	setArmorType(a_armorType);
	return true;
}
Armor::~Armor(){}
void Armor::damageArmor(int damage)
{
	armorHealth -= (1- damageResistance) * damage;
	if(armorHealth<0) armorHealth =0; 
}

bool Armor::armorDepleted(void)
{
	if(armorHealth <= 0) return true;
	else return false;
}
float Armor::getArmorHealth(){return armorHealth;}
float Armor::getDamageResistance(){return damageResistance;}
void Armor::setArmorHealth(float a_armorHealth)
{
	 a_armorHealth = armorHealth;
}
void Armor::setArmorType(int a_armorType)
{
	armorType = a_armorType;
	damageResistance = 0.25f * armorType;
}
int Armor::getArmorType(){return armorType;}
void Armor::setDamageResistance(float a_damageResistance){damageResistance = a_damageResistance;}
void Armor::armorHealthRestore()
{
	armorHealth = 80.0;
	
}
