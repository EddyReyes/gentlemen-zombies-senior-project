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
void HUD::draw()
{
	healthBar->draw();
	armorBar->draw();
	weapon->draw();
	playerID->draw();
	playerMoney->draw();
}
void HUD::updateHealthBar()
{
	
}
void HUD::updateArmorBar()
{



}
void HUD::updateWeapon()
{


}
void HUD::updatePlayerMoney()
{


}

void HUD::setHealthBarImage(std::string filename)
{
	healthBar->setImage(filename);
}
void HUD::setArmorBarImage(std::string filename)
{
	armorBar->setImage(filename);
}
void HUD::setWeaponImage(std::string filename)
{
	weapon->setImage(filename);
}
void HUD::setPlayerMoneyImage(std::string filename)
{
	playerMoney->textInfo("Arial", 26,
				D3DCOLOR_ARGB(255, 255, 255, 0), "000");
	playerMoney->setTextBoxParameters(30.0, 60.0, 400, 400, 25);
}
void HUD::setPlayerID(int ID)
{
	 
}
void HUD::setPlayerIDImage(std::string filename)
{
	playerID->draw();
}
void HUD::setHudPosition()
{
	
}