#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "entity.h"
#include "imageManager.h"

class HUD
{
	private:
		HudImage * armor;
		entity * plyr;
		HudImage ** images;
		imageManager * imgMgr;
		dxManager * dxMgr;
	public:
		HUD();
		~HUD();
		void draw();
		void loadFromFile(std::string filename, dxManager * a_dxMgr);
		void update();
		void initPositions(std::string filename);
		void setPlayer(entity * a_Player);
};