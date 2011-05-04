#include "Player.h"


Player::Player()
{
	//Player life points is set to 100;
	//Players damage resistance is at 50%
	PlayerHealth = 100.0;
	damageResistance = 0.50;
	money = 0;
	m_char = NULL;

}
Player::Player(dxManager* a_dxMgr, char* file)
{
	PlayerHealth = 100.0;
	damageResistance = 0.50;
	money = 0;
	m_char = new object(a_dxMgr,file);
	m_char->setPosition(0,0,0);
}
Player::~Player()
{
	delete m_char;
}
float Player::getHealth()
{
	//getting the Players health.
	return PlayerHealth;
}

void Player::setHealth(float a_health)
{
	// setting the Players health
	
	a_health = PlayerHealth;
}

void Player::healthRegenerate(float healthPack)
{
	//updateing Players health.
	//(When Player receave a health pack it will add more life poits to Player health.)
	float maxHealth = 100.0;
	PlayerHealth += healthPack;
	if(PlayerHealth > maxHealth)
		PlayerHealth = maxHealth;
}

void  Player::PlayerDamage(float damage)
{
	//udateing the Players current health: health is being depleated. 
	PlayerHealth -= (1 - damageResistance) * damage;
	if(PlayerHealth < 0) PlayerHealth = 0;
	// if health equals zero then the Player is dead and the health will print out zero for remaining health.
}

float Player::getMoney()
{
	return money;
}

void Player::addMoney(float recieve)
{
	float maxMoney = 50;
	money += recieve;
	if(money > maxMoney)
	money = maxMoney;
}

void Player::setMoney(float a_money)
{
	a_money = money;
}
void Player::Draw()
{
	m_char->draw();
}
void Player::movePlayer(float a_x,float a_y)
{
	m_char->setPosition(a_x,a_y,0.0f);
}
