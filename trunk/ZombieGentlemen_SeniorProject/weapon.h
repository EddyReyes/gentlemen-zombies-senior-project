#pragma once

class Weapon
{
	private:
		int damage;
		int hitPoints;
		int weaponCost;
		int weaponSpeed;
	public:
		int damageGiven(void);
		int damageReceived(void);
		int speed(void);
		float cost(void);
		int shovle();
		Weapon();
		~Weapon();	
};

class PlayerWeapon
{
	private:
		int playerWeaponDamage;
		int playerWeaponType;
		int playerWeaponUpdate;
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