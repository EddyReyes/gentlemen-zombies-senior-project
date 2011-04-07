#include "HUD.h"

HUD::HUD(){}
HUD::HUD(std::string filename, dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	healthBar = new HudImage(dxMgr, filename);
	armorBar = new HudImage(dxMgr, filename);
	weapon = new HudImage(dxMgr, filename);
	playerID = new DXText(dxMgr, filename);
	playerMoney = new DXText(dxMgr, filename);
	hudPosition.x = 0;
	hudPosition.y = 0;
}
HUD::~HUD()
{
	healthBar->~HudImage();
	healthBar = NULL;
	armorBar->~HudImage();
	armorBar = NULL;
	weapon->~HudImage();
	weapon = NULL;
	playerID->~DXText();
	playerID = NULL;
	playerMoney->~DXText();
	playerMoney = NULL;
}