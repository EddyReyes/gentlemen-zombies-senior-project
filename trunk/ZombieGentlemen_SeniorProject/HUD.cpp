#include "HUD.h"
#include "playerCharacter.h"

HUD::HUD(){}
HUD::HUD(dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	hudBackground = NULL;
	healthBar = NULL;
	armorBar = NULL;
	weapon = NULL;
	bagOfMoney = NULL;
	playerID = NULL;
	playerIDNumber = NULL;
	playerMoney = NULL;
	hudPosition.x = NULL;
	hudPosition.y = NULL;
}
HUD::~HUD()
{
	if(hudBackground)
	hudBackground->~HudImage();
	hudBackground = NULL;
	if(healthBar)
	healthBar->~HudImage();
	healthBar = NULL;
	if(armorBar)
	armorBar->~HudImage();
	armorBar = NULL;
	if(weapon)
	weapon->~HudImage();
	weapon = NULL;
	if(bagOfMoney)
	bagOfMoney->~HudImage();
	bagOfMoney= NULL;
	if(playerID)
	playerID->~HudImage();
	playerID = NULL;
	if(playerMoney)
	playerMoney->~DXText();
	playerMoney = NULL;
}
void HUD::draw()
{
	if(hudBackground)
	hudBackground->draw();
	if(healthBar)
	healthBar->draw();
	if(armorBar)
	armorBar->draw();
	if(weapon)
	weapon->draw();
	if(bagOfMoney)
	bagOfMoney->draw();
	if(playerID)
	playerID->draw();
	if(playerMoney)
	playerMoney->draw();
}
void HUD::updateHealthBar()
{
	/*if (healthBar)
	{
		healthBar->getWidth();
		healthBar++;
	}
	else
	{ healthBar--; }*/
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
	setHudImage("images/new_hud.bmp");
	setHealthBarImage("images/healthBar.bmp");
	setArmorBarImage("images/armorBar.bmp");
	setWeaponImage("images/sword.bmp");
	setBagOfMoneyImage("images/moneyBag.bmp");
	//setCurrencyValueImage("images/moneyTextBox.bmp");
	setPlayerIDImage("images/WillConcept.bmp");
	setHudPosition(2.0f, 5.0f);
	
}
void HUD::setHudImage(std::string filename)
{
	if(hudBackground == NULL)
	{
		hudBackground = new HudImage(dxMgr, filename);
	}
	else if(hudBackground)
	{
		hudBackground->~HudImage();
		hudBackground = new HudImage(dxMgr, filename);
	}
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
void HUD::setBagOfMoneyImage(std::string filename)
{
	if(bagOfMoney == NULL)
	{
		bagOfMoney = new HudImage(dxMgr, filename);
	}
	else if(bagOfMoney)
	{
		bagOfMoney->~HudImage();
		bagOfMoney = new HudImage(dxMgr, filename);
	}
}
void HUD::setCurrencyValueImage(std::string filename)
{
	playerMoney->toggleImage();
	playerMoney->textInfo("Arial", 26,
				D3DCOLOR_ARGB(255, 0, 0, 255), "000");
	playerMoney->setRect(80, 100, 25, 60);
	playerMoney->setTextBoxParameters(30.0, 60.0, 30, 80, 25);
}
void HUD::setPlayerID(int ID)
{
	 //ID = prints player 1, 2, 3, 4
}
void HUD::setPlayerIDImage(std::string filename)
{
	if(playerID == NULL)
	{
		playerID = new HudImage(dxMgr, filename);
	}
	else if(playerID)
	{
		playerID->~HudImage();
		playerID = new HudImage(dxMgr, filename);
	}
}
void HUD::setHudPosition(float a_x, float a_y)
{
	hudPosition.x = a_x;
	hudPosition.y = a_y;
	if(hudBackground)
		hudBackground->setParameters(hudBackground->getWidth() - 50 + a_x, hudBackground->getHeight() - 50 + a_y,
		hudBackground->getXPosition() + 0 + a_x, hudBackground->getYPosition() - 10 + a_y);
	if(playerID)
		playerID->setParameters(playerID->getWidth() - 200 + a_x, playerID->getHeight() - 200 + a_y,
		playerID->getXPosition() + 17 + a_x, playerID->getYPosition() + 15 + a_y);
	if(healthBar)
		healthBar->setParameters(healthBar->getWidth() - 160 + a_x, healthBar->getHeight() - 250 + a_y,
		healthBar->getXPosition() + 85 + a_x, healthBar->getYPosition() + 20 + a_y);
	if(armorBar)
		armorBar->setParameters(armorBar->getWidth() - 175 + a_x, armorBar->getHeight() - 250 + a_y,
		armorBar->getXPosition() + 85 + a_x, armorBar->getYPosition()+ 35 + a_y);
	if(weapon)
		weapon->setParameters(weapon->getWidth() - 180 + a_x, weapon->getHeight() - 180 + a_y,
		weapon->getXPosition() + 85 + a_x, weapon->getYPosition() + 95 + a_y);
	if(bagOfMoney)
		bagOfMoney->setParameters(bagOfMoney->getWidth() - 180 + a_x, bagOfMoney->getHeight() - 180 + a_y,
		bagOfMoney->getXPosition() + 10 + a_x, bagOfMoney->getYPosition() + 72 + a_y);
}	