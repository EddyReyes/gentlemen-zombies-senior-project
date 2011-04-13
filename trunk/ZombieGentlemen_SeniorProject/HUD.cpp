#include "HUD.h"
#include "playerCharacter.h"

HUD::HUD(){}
HUD::HUD(dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	healthBar = NULL;
	armorBar = NULL;
	weapon = NULL;
	playerID = NULL;
	playerMoney = NULL;
	hudPosition.x = NULL;
	hudPosition.y = NULL;
}
HUD::~HUD()
{
	if(healthBar)
	healthBar->~HudImage();
	healthBar = NULL;
	if(armorBar)
	armorBar->~HudImage();
	armorBar = NULL;
	if(weapon)
	weapon->~HudImage();
	weapon = NULL;
	if(playerID)
	playerID->~DXText();
	playerID = NULL;
	if(playerMoney)
	playerMoney->~DXText();
	playerMoney = NULL;
}
void HUD::draw()
{
	if(healthBar)
	healthBar->draw();
	if(armorBar)
	armorBar->draw();
	if(weapon)
	weapon->draw();
	if(playerID)
	playerID->draw();
	if(playerMoney)
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
void HUD::initDefaultPositions()
{

}

void HUD::setHealthBarImage(std::string filename)
{
	if(healthBar == NULL)
	{
		healthBar = new HudImage(dxMgr, filename);
	}
	else if(healthBar)
	{
		healthBar->~HudImage();
		healthBar = new HudImage(dxMgr, filename);
	}
}
void HUD::setArmorBarImage(std::string filename)
{
	if(armorBar == NULL)
	{
		armorBar = new HudImage(dxMgr, filename);
	}
	else if(armorBar)
	{
		armorBar->~HudImage();
		armorBar = new HudImage(dxMgr, filename);
	}
}
void HUD::setWeaponImage(std::string filename)
{
	if(weapon == NULL)
	{
		weapon = new HudImage(dxMgr, filename);
	}
	else if(weapon)
	{
		weapon->~HudImage();
		weapon = new HudImage(dxMgr, filename);
	}
}
void HUD::setPlayerMoneyImage(std::string filename)
{
	playerMoney->textInfo("Arial", 26,
				D3DCOLOR_ARGB(255, 255, 255, 0), "000");
	playerMoney->setTextBoxParameters(30.0, 60.0, 400, 400, 25);
}
void HUD::setPlayerID(int ID)
{
	 //ID = prints player 1, 2, 3, 4
}
void HUD::setPlayerIDImage(std::string filename)
{
	playerID->draw();
}
void HUD::setHudPosition(float a_x, float a_y)
{
	hudPosition.x = a_x;
	hudPosition.y = a_y;
	if(healthBar)
	healthBar->setParameters(healthBar->getWidth(), healthBar->getHeight(),
		healthBar->getXPosition() + a_x, healthBar->getYPosition() + a_y);
	if(armorBar)
	armorBar->setParameters(armorBar->getWidth(), armorBar->getHeight(),
		armorBar->getXPosition() + a_x, armorBar->getYPosition() + a_y);
	if(weapon)
	weapon->setParameters(weapon->getWidth(), weapon->getHeight(),
		weapon->getXPosition() + a_x, weapon->getYPosition() + a_y);
	//playerID.....
}	
