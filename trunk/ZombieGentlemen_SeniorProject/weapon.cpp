#include "weapon.h"

Weapon::Weapon()
{
	damage = 0;
	hitPoints = 0;
	weaponCost = 0;
	weaponSpeed = 0;
}
Weapon::~Weapon()
{	
}
int Weapon::damageGiven(int a_damage)
{
	damage = a_damage;
	return damage;
}
int Weapon::damageReceived(int a_hitPoints)
{
	hitPoints = a_hitPoints;
	return hitPoints;
}
int Weapon::weaponDamageType(void)
{
	return 0;
}
float Weapon::cost(int cost)
{
	
	return cost;
}
int Weapon::shovle()
{
	// the shovle only have 5 attack points. basicly it can only fight weak enemies.
	int hitPoints = 5;
	int damage = hitPoints;
	return damage;
};
int PlayerWeapon::weaponType(void)
{
	return 0;
}
int PlayerWeapon::weaponDamageUpdate(void)
{
	return 0;
}
int PlayerWeapon::weaponPickup(void)
{
	return 0;
}
int PlayerWeapon::weaponPickupUpdate(void)
{
	return 0;
}
PlayerWeapon::PlayerWeapon()
{
}
PlayerWeapon::~PlayerWeapon()
{
}
int NPCWeapon::npcWeaponType(void)
{
	return 0;
}
int NPCWeapon::npcWeaponDamageUpdate(void)
{
	return 0;
}
int NPCWeapon::npcWeaponPickup(void)
{
	return 0;
}
int NPCWeapon::npcWeaponPickupUpdate(void)
{
	return 0;
}
NPCWeapon::NPCWeapon()
{
}
NPCWeapon::~NPCWeapon()
{
}