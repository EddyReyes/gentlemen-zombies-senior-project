#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "player.h"
#include "imageManager.h"

class HUD
{
	private:
		HudImage * armor;
		player * plyr;
		HudImage ** images;
		imageManager * imgMgr;
		dxManager * dxMgr;
		float timer;
	public:
		HUD();
		~HUD();
		void draw();
		void loadFromFile(std::string filename, dxManager * a_dxMgr);
		void update(float updateTime);
		void initPositions(std::string filename);
		void setPlayer(player * a_Player);
};