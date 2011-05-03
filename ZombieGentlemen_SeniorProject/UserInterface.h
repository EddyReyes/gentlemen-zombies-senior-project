#pragma once
#include "playerCharacter.h"
#include "EnemyCharacter.h"
#include "HUD.h"

class UserInterface
{
	private:
		PlayerCharacter * character;
		EnemyCharacter * enemyCharacter;
		HUD * hudElement;
	public:
		UserInterface();
		~UserInterface();
		bool playerEngagesEnemy();
		bool playerChecksHealth();
		bool playerChecksArmor();
		void playerAttacks();
		void playerAttacked();
		void playerDied();
		void enemyDied();
		void EnemyDropsCoin();
		void playerCurrencyRecieved();
		void updatePlayerCurrency();
};