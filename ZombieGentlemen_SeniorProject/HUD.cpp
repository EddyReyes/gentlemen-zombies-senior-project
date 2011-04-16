#include "HUD.h"



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
	player = new PlayerCharacter();
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
void HUD::updateHealthBar(int damage)
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
void HUD::initDefaultPositions(float a_x, float a_y)
{
	hudBackground->setParameters(220.0, 220.0, 2.0 + a_x, 2.0 + a_y);
	playerID->setParameters(70.0, 70.0, 19.0 + a_x, 27.0 + a_y);
	healthBar->setParameters(95.0, 12.0, 95.0 + a_x, 44.0 + a_y);
	armorBar->setParameters(75.0, 12.0, 95.0 + a_x, 72.0 + a_y);	
	weapon->setParameters(80.0, 80.0, 93.0 + a_x, 97.0 + a_y);
	bagOfMoney->setParameters(75.0, 75.0, 22.0 + a_x, 95.0 + a_y);
	//playerMoney->setTextBoxParameters(68.0, 45.0, 72.0 + a_x, 100.0 + a_y, 12); 
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
	//playerMoney->toggleImage();
	playerMoney = new DXText(dxMgr, filename);

	playerMoney->textInfo("Arial", 11,
				D3DCOLOR_ARGB(255, 0, 0, 0), "Loading");
	playerMoney->setTextBoxParameters(68, 45, 72, 100, 12);

}
void HUD::setPlayerID(int ID)
{
	 //ID = prints player 1, 2, 3, 4
}
void HUD::setHudPosition(float a_x, float a_y)
{
	hudPosition.x = a_x;
	hudPosition.y = a_y;
	if(hudBackground)
		hudBackground->setParameters(hudBackground->getWidth() + a_x, hudBackground->getHeight() + a_y,
		hudBackground->getXPosition() + a_x, hudBackground->getYPosition() + a_y);
	if(playerID)
		playerID->setParameters(playerID->getWidth() - 200 + a_x, playerID->getHeight() - 200 + a_y,
		playerID->getXPosition() + 17 + a_x, playerID->getYPosition() + 15 + a_y);

		playerID->setParameters(playerID->getWidth() + a_x, playerID->getHeight() + a_y,
		playerID->getXPosition() + a_x, playerID->getYPosition() + a_y);

	if(healthBar)
		healthBar->setParameters(healthBar->getWidth() + a_x, healthBar->getHeight() + a_y,
		healthBar->getXPosition() + a_x, healthBar->getYPosition() + a_y);
	if(armorBar)
		armorBar->setParameters(armorBar->getWidth() + a_x, armorBar->getHeight() + a_y,
		armorBar->getXPosition() + a_x, armorBar->getYPosition() + a_y);
	if(weapon)
		weapon->setParameters(weapon->getWidth() + a_x, weapon->getHeight() + a_y,
		weapon->getXPosition() + a_x, weapon->getYPosition() + a_y);
	if(bagOfMoney)
		bagOfMoney->setParameters(bagOfMoney->getWidth() + a_x, bagOfMoney->getHeight() + a_y,
		bagOfMoney->getXPosition() + a_x, bagOfMoney->getYPosition() + a_y);
}	
void HUD::updateCurrencyValueImage()
{
	char updateBuffer[50];
	sprintf_s(updateBuffer, "Money %i \n",player->getMoney());
	playerMoney->setDialog(updateBuffer);

}
void HUD::setPlayer(PlayerCharacter * a_player)
{
	player = a_player;
}