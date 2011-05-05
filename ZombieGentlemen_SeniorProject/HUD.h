#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "Player.h"
#include "imageManager.h"
#include "armor.h"

class HUD
{
	private:
		//HudImage * hudBackground;
		//HudImage * barHolder;
		//HudImage * barHolder2;
		HudImage * healthBar;
		HudImage * armorBar;
		//HudImage * weapon;
		//HudImage * bagOfMoney;
		//HudImage * PlayerID;
		Player * plyr;
		DXText * PlayerMoney;
		HudImage ** images;
		imageManager * imgMgr;
		dxManager * dxMgr;
	public:
		HUD();
		~HUD();
		void draw();
		void loadFromFile(std::string filename, std::string textParam, dxManager * a_dxMgr);
		void update();
		void initPositions(std::string filename);
		void setPlayer(Player * a_Player);
};