#include "armor.h"

Armor::Armor(){}
bool Armor::initPlayerArmor(int a_armorType)
{
	if (a_armorType < 1 || a_armorType > 3) return false;
	armorHealth = 100;
	setArmorType(a_armorType);
	return true;
}
Armor::~Armor(){}
void Armor::damagedArmor(int damage)
{
	armorHealth -= (1- damageResistance) * damage;
	if(armorHealth<0) armorHealth =0; 
}
void Armor::armorRegenerate(void)
{
	armorHealth = 100;
}
bool Armor::armorDepleted(void)
{
	if(armorHealth <= 0) return true;
	else return false;
}
float Armor::getArmorHealth(){return armorHealth;}
float Armor::getDamageResistance(){return damageResistance;}
void Armor::setArmorHealth(int a_armorHealth)
{
	armorHealth = a_armorHealth;
}
void Armor::setArmorType(int a_armorType)
{
	armorType = a_armorType;
	damageResistance = 0.25 * armorType;
}
int Armor::getArmorType(){return armorType;}
void Armor::setDamageResistance(int a_damageResistance){damageResistance = a_damageResistance;}
