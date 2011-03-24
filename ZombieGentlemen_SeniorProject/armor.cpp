#include "armor.h"

int PlayerArmor::damagedArmor(void)
{
	hitPoints = 100;
	armorDamage = 25;
	bool isPlayerHit = true;
	//if player takes damage with armor present,  damage takes away hitPoints
	if (player == isPlayerHit)
	{
		updateArmor = hitPoints - armorDamage;
		return updateArmor;
	}

	//if 


	return armorDamage;
}
int PlayerArmor::armorRegenerated(void)
{
	return 0;
}
int PlayerArmor::armorDepleted(void)
{
	return 0;
}
int PlayerArmor::armorPickup(void)
{
	return 0;
}
PlayerArmor::PlayerArmor()
{
	int playerArmor = 100;
}
PlayerArmor::~PlayerArmor()
{

}
int NPCArmor::npcDamagedArmor(void)
{
	return 0;
}
int NPCArmor::npcArmorRegenerated(void)
{
	return 0;
}
int NPCArmor::npcArmorDepleted(void)
{
	return 0;
}
int NPCArmor::npcArmorPickup(void)
{
	return 0;
}
NPCArmor::NPCArmor()
{
	int npcArmor = 100;
}
NPCArmor::~NPCArmor()
{

}