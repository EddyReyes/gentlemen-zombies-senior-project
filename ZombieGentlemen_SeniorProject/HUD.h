#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "playerCharacter.h"
#include "imageManager.h"
#include "armor.h"

class HUD
{
	private:
		HudImage * hudBackground;
		HudImage * barHolder;
		HudImage * barHolder2;
		HudImage * healthBar;
		HudImage * armorBar;
		HudImage * weapon;
		HudImage * bagOfMoney;
		HudImage * playerID;
		PlayerCharacter * player;
		DXText * playerIDNumber;
		DXText * playerMoney;
		imageManager * imgMgr;
		dxManager * dxMgr;

	public:
		HUD();
		HUD(dxManager * a_dxMgr);
		~HUD();
		void draw();
		void loadFromFile();
		void update();





		void updateHealthBarDamage();
		void useHealthPack();
		void updateArmorBarDamage(int a_armorType);
		void useArmorPickUp();
		void updateWeapon(std::string filename);
		void updateCurrencyValue();
		void initDefaultPositions(float a_x, float a_y);
		void setHudImage(std::string filename);
		void setPlayerIDImage(std::string filename);
		void setBarHolderImage(std::string filename);
		void setHealthBarImage(std::string filename);
		void setBarHolder2Image(std::string filename);
		void setArmorBarImage(std::string filename);
		void setWeaponImage(std::string filename);
		void setBagOfMoneyImage(std::string filename);
		void setCurrencyValue(std::string filename);
		void setPlayer(PlayerCharacter * a_player);
};