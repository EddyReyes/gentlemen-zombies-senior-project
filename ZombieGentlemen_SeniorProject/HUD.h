#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "playerCharacter.h"
#include "EnemyCharacter.h"


class HUD
{
private:

	HudImage * hudBackground;
	HudImage * healthBar;
	HudImage * armorBar;
	HudImage * weapon;
	HudImage * bagOfMoney;
	HudImage * playerID;
	PlayerCharacter * player;
	EnemyCharacter * enemy;
	DXText * playerIDNumber;
	DXText * playerMoney;
	D3DXVECTOR2 hudPosition;
	dxManager * dxMgr;
		
	
public:
	HUD();
	HUD(dxManager * a_dxMgr);
	~HUD();
	void draw();
	void updateHealthBar(int damage);
	void updateArmorBar();
	void updateWeapon();
	void updatePlayerMoney();
	void initDefaultPositions(float a_x, float a_y);
	void setHudImage(std::string filename);
	void setHealthBarImage(std::string filename);
	void setArmorBarImage(std::string filename);
	void setWeaponImage(std::string filename);
	void setBagOfMoneyImage(std::string filename);
	void setCurrencyValue(std::string filename);
	void setPlayerID(int ID);
	void setPlayerIDImage(std::string filename);
	void setHudPosition(float a_x, float a_y);
	void updateCurrencyValue();
	void setPlayer(PlayerCharacter * a_player);
	void addMoney(float moneyRecieve);
	
};