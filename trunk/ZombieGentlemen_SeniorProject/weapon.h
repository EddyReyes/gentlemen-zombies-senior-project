#pragma once

class Weapon
{
	private:
		int damage;
		int hitPoints;
		int weaponCost;
		int weaponSpeed;
		
	public:
		Weapon();
		~Weapon();
		int damageGiven(int a_damage);
		int damageReceived(int a_hitPoints);
		int weaponDamageType(void);
		float cost(float a_cost);
		int shovle();
			
};

class PlayerWeapon
{
	private:
		int PlayerWeaponDamage;
		int PlayerWeaponType;
		int PlayerWeaponUpdate;
	public:
		int weaponType(void);
		int weaponDamageUpdate(void);
		int weaponPickup(void);
		int weaponPickupUpdate(void);
		PlayerWeapon();
		~PlayerWeapon();
};

class NPCWeapon
{
	private:
		int npcWeaponDamage;
		int npcWeaponTypes;
		int npcWeaponUpdate;
	public:
		int npcWeaponType(void);
		int npcWeaponDamageUpdate(void);
		int npcWeaponPickup(void);
		int npcWeaponPickupUpdate(void);
		NPCWeapon();
		~NPCWeapon();
};