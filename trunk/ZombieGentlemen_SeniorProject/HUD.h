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
};