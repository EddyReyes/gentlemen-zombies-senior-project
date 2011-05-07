#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "entity.h"
#include "imageManager.h"

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
		entity * plyr;
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
		void setPlayer(entity * a_Player);
};