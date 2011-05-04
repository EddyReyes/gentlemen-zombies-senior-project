#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "Player.h"
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
		HudImage * PlayerID;
		Player * plyr;
		DXText * PlayerIDNumber;
		DXText * PlayerMoney;
		imageManager * imgMgr;
		dxManager * dxMgr;

	public:
		HUD();
		~HUD();
		void draw();
		void loadFromFile(std::string filename, dxManager * a_dxMgr);
		void update();
		void initDefaultPositions(float a_x, float a_y);
		void setPlayer(Player * a_Player);

		// the following functions must be removed
		void updateHealthBarDamage();
		void useHealthPack();
		void updateArmorBarDamage(int a_armorType);
		void useArmorPickUp();
		void updateWeapon(std::string filename);
		void updateCurrencyValue();
		void setHudImage(std::string filename);
		void setPlayerIDImage(std::string filename);
		void setBarHolderImage(std::string filename);
		void setHealthBarImage(std::string filename);
		void setBarHolder2Image(std::string filename);
		void setArmorBarImage(std::string filename);
		void setWeaponImage(std::string filename);
		void setBagOfMoneyImage(std::string filename);
		void setCurrencyValue(std::string filename);
		
};