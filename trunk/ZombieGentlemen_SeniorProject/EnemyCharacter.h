#pragma once

class EnemyCharacter
{
private:
	float enemieHealth;
	float damageResistance;
	int enemieType;
public:
	EnemyCharacter();
	~EnemyCharacter();
	float getEnemieHealth();
	void setEnemieHealth(int);
	int getEnemieType();
	void setEnemieType(int a_armorType);
	bool initEnemie(int a_enmeieType);
	void Enemiedamage(int damage);
};