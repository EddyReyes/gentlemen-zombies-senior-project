#pragma once

//work in progress, typical classes started here

class PlayerArmor
{
	private:
		int playerArmor;
		int armorPoints;
		int armorDamage;
		int damageResistance;
		int cost;
	public:
		int damagedArmor(void);
		int armorRegenerated(void);
		int armorDepleted(void);
		int armorPickup(void);
		PlayerArmor();
		~PlayerArmor();
};

class NPCArmor
{
	private:
		int npcArmor;
		int npcArmorPoints;
		int npcArmorDamage;
		int npcDamageResistance;
	public:
		int npcDamagedArmor(void);
		int npcArmorRegenerated(void);
		int npcArmorDepleted(void);
		int npcArmorPickup(void);
		NPCArmor();
		~NPCArmor();
};