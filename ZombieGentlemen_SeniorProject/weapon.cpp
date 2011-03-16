#include "weapon.h"

int Weapon::damageGiven(void)
{

	return 0;
}
int Weapon::damageReceived(void)
{
	return 0;
}
int Weapon::speed(void)
{
	return 0;
}
float Weapon::cost(void)
{
	return 0;
}
int Weapon::shovle()
{
	// the shovle only have 5 attack points. basicly it can only fight weak enemies.
	int hitPoints = 5;
	int damage = hitPoints;
	return damage;
};
Weapon::Weapon()
{
	//damage points will always be set to zero. 
	damage = 0;
}
Weapon::~Weapon()
{
}
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