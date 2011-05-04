#include "player.h"


player::player()
{
	//Player life points is set to 100;
	//Players damage resistance is at 50%
	playerHealth = 100.0;
	damageResistance = 0.50;
	money = 0;
	m_char = NULL;

}
player::player(dxManager* a_dxMgr, char* file)
{
	playerHealth = 100.0;
	damageResistance = 0.50;
	money = 0;
	m_char = new object(a_dxMgr,file);
	m_char->setPosition(0,0,0);
}
player::~player()
{
	delete m_char;
}
float player::getHealth()
{
	//getting the players health.
	return playerHealth;
}

void player::setHealth(float a_health)
{
	// setting the players health
	
	a_health = playerHealth;
}

void player::healthRegenerate(float healthPack)
{
	//updateing players health.
	//(When player receave a health pack it will add more life poits to player health.)
	float maxHealth = 100.0;
	playerHealth += healthPack;
	if(playerHealth > maxHealth)
		playerHealth = maxHealth;
}

void  player::playerDamage(float damage)
{
	//udateing the players current health: health is being depleated. 
	playerHealth -= (1 - damageResistance) * damage;
	if(playerHealth < 0) playerHealth = 0;
	// if health equals zero then the player is dead and the health will print out zero for remaining health.
}

float player::getMoney()
{
	return money;
}

void player::addMoney(float recieve)
{
	float maxMoney = 50;
	money += recieve;
	if(money > maxMoney)
	money = maxMoney;
}

void player::setMoney(float a_money)
{
	a_money = money;
}
void player::Draw()
{
	m_char->draw();
}
void player::moveplayer(float a_x,float a_y)
{
	m_char->setPosition(a_x,a_y,0.0f);
}
