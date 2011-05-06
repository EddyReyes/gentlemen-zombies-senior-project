#include "Player.h"


Player::Player()
{
	m_object = NULL;
}

void Player::init(object * a_object)
{
	health = 100.0f;
	m_object = a_object;
	money = 0;
}
Player::~Player()
{
	// the players object does not get destroyed becuase it is handled by the object manager
}

void Player::healthRegenerate(float healthPack)
{
	//updateing Players health.
	//(When Player receave a health pack it will add more life poits to Player health.)
	float maxHealth = 100.0;
	health += healthPack;
	if(health > maxHealth)
		health = maxHealth;
}

void  Player::damage(float damage)
{
	//udateing the Players current health: health is being depleated. 
	health -= (1 - damageResistance) * damage;
	if(health < 0) health = 0;
	// if health equals zero then the Player is dead and the health will print out zero for remaining health.
}

void Player::addMoney(float recieve)
{
	float maxMoney = 50;
	money += recieve;
	if(money > maxMoney)
	money = maxMoney;
}
void Player::setMoney(float a_money){a_money = money;}
void Player::setHealth(float a_health){health  = a_health;}

float Player::getHealth(){return health;}
float Player::getMoney(){return money;}