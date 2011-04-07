#pragma once
#include "DXText.h"
#include "HudImage.h"

class HUD
{
private:
	HudImage * healthBar;
	HudImage * armorBar;
	HudImage * weapon;
	DXText * playerID;
	DXText * playerMoney;
	D3DXVECTOR2 hudPosition;
	dxManager * dxMgr;
	
	
public:
	HUD();
	HUD(std::string filename, dxManager * a_dxMgr);
	~HUD();
	void draw();
	void updateHealthBar();
	void updateArmorBar();
	void updateWeapon();
	void updatePlayerMoney();

	void setHealthBarImage(std::string filename);
	void setArmorBarImage(std::string filename);
	void setWeaponImage(std::string filename);
	void setPlayerMoneyImage(std::string filename);
	void setPlayerID(int ID);
	void setPlayerIDImage(std::string filename);
	void setHudPosition();
};