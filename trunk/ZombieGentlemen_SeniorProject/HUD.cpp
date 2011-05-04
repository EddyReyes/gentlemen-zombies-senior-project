#include "HUD.h"

HUD::HUD()
{
	dxMgr = NULL;
	hudBackground = NULL;
	barHolder = NULL;
	barHolder2 = NULL;
	healthBar = NULL;
	armorBar = NULL;
	weapon = NULL;
	bagOfMoney = NULL;
	playerID = NULL;
	playerIDNumber = NULL;
	playerMoney = NULL;
	player = NULL;
}
HUD::~HUD()
{
	if(hudBackground)
	hudBackground->~HudImage();
	hudBackground = NULL;
	if(barHolder)
	barHolder->~HudImage();
	barHolder = NULL;
	if(barHolder2)
	barHolder2->~HudImage();
	barHolder2 = NULL;
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
	// destroy image manager (also destroys all images)
	imgMgr->~imageManager();
	imgMgr = NULL;
}
void HUD::draw()
{
	if(hudBackground)
	hudBackground->draw();
	if(barHolder)
	barHolder->draw();
	if(barHolder2)
	barHolder2->draw();
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

/****************************************************************
* loadFromFile
* takes in one text file, and loads images into an image manager
* from the image manager all HudImages are insansiated with image
* data
****************************************************************/
void HUD::loadFromFile(std::string filename, dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	imgMgr = new imageManager();
	imgMgr->initImageManager(filename, dxMgr);

	hudBackground = new HudImage(dxMgr, imgMgr->getImage(0), imgMgr->getImageInfo(0));
}
/****************************************************************
* update
* updates entire hud
* health bar is updated to illustrate players current health
* armor bar is updated to illustrate players current health
* money is updated to illustrate players current funds
****************************************************************/
void HUD::update()
{
	if(player != NULL)
	{
		healthBar->setParameters(player->getHealth(), healthBar->getHeight(), healthBar->getXPosition(), healthBar->getYPosition());
		
	}
}

/****************************************************************
* initDefaultPositions
* sets the default positions of the hud items
* also takes in an offset for the hud to move around the screen
****************************************************************/
void HUD::initDefaultPositions(float a_x, float a_y)
{
	hudBackground->setParameters(220.0f, 220.0f, 2.0f + a_x, 2.0f + a_y);
	playerID->setParameters(70.0f, 70.0f, 19.0f + a_x, 27.0f + a_y);
	barHolder->setParameters(124.0f, 100.0f, 82.0f + a_x, 9.0f + a_y);
	healthBar->setParameters(100.0f, 12.0f, 95.0f + a_x, 43.0f + a_y);
	barHolder2->setParameters(95.0f, 100.0f, 90.0f + a_x, 37.0f + a_y);
	armorBar->setParameters(80.0f, 12.0f, 95.0f + a_x, 71.0f + a_y);	
	weapon->setParameters(80.0f, 80.0f, 95.0f + a_x, 97.0f + a_y);
	bagOfMoney->setParameters(75.0f, 75.0f, 22.0f + a_x, 95.0f + a_y);
}
/****************************************************************
* setPlayer
* sets the player pointer
* must be called in order for the updates to take effect
****************************************************************/
void HUD::setPlayer(PlayerCharacter * a_player){player = a_player;}

//The following methods must be removed*********************************

void HUD::updateHealthBarDamage()
{
	float decrement;
	player->playerDamage(15);
	decrement = player->getHealth();
	healthBar = new HudImage(dxMgr, "images/healthBar.bmp");
	healthBar->setParameters(decrement, 12.0, 95.0, 43.0);
}
void HUD::useHealthPack()
{
	float increment;
	player->healthRegenerate(20);
	increment = player->getHealth();
	healthBar = new HudImage(dxMgr, "images/healthBar.bmp");
	healthBar->setParameters(increment, 12.0, 95.0, 43.0);
}


// the following methods have been commented to avoid errors when compiling
// the reason they generate errors is becuase there is no longer an armor pointer



//void HUD::updateArmorBarDamage(int a_armorType)
//{
//	float decrement;
//	float stdWidth = 10.0;
//	decrement = armor->getArmorHealth() - stdWidth;
//	//armor->initPlayerArmor(a_armorType);
//	//armor->damageArmor(6);
//	decrement = armor->getArmorHealth();
//	armorBar = new HudImage(dxMgr, "images/armorBar.bmp");
//	armorBar->setParameters(decrement, 12.0, 95.0, 71.0);
//}
//void HUD::useArmorPickUp()
//{
//	float newArmor;
//	armor->armorHealthRestore();
//	newArmor = armor->getArmorHealth();
//	armorBar = new HudImage(dxMgr, "images/armorBar.bmp");
//	armorBar->setParameters(newArmor, armorBar->getYPosition(), 95.0, 71.0);
//}
void HUD::updateWeapon(std::string filename)
{
	if(weapon)
	{	
		weapon = new HudImage(dxMgr, filename);
		weapon->setParameters(80.0, 80.0, 98.0, 97.0);
	}
}
void HUD::updateCurrencyValue()
{
	char updateBuffer[50];
  	sprintf_s(updateBuffer, "Mny %.00f/50\n Hp %.00f", player->getMoney(), healthBar->getWidth());
	playerMoney->setDialog(updateBuffer);
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
void HUD::setBarHolderImage(std::string filename)
{
	if(barHolder == NULL)
	{
		barHolder = new HudImage(dxMgr, filename);
	}
	else if(barHolder)
	{
		barHolder->~HudImage();
		barHolder = new HudImage(dxMgr, filename);
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
void HUD::setBarHolder2Image(std::string filename)
{
	if(barHolder2 == NULL)
	{
		barHolder2 = new HudImage(dxMgr, filename);
	}
	else if(barHolder2)
	{
		barHolder2->~HudImage();
		barHolder2 = new HudImage(dxMgr, filename);
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
void HUD::setCurrencyValue(std::string filename)
{
	playerMoney = new DXText(dxMgr, filename);
	playerMoney->textInfo("Arial", 11,
				D3DCOLOR_ARGB(255, 0, 0, 0), "Loading");
	playerMoney->setTextBoxParameters(68, 55, 72, 100, 12);

}
