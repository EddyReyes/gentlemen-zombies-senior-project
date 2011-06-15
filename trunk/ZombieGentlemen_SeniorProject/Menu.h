#pragma once
#include "DXText.h"
#include "HudImage.h"
#include "imageManager.h"
#include "stringArray.h"
#include "inputData.h"


/*the menu class will be responsible for the title screen
as well as the in game stores*/
class Menu
{
	private:
		int selected;
		imageManager* imgMan;
		DXText ** options; //array of options
		HudImage * background;
		stringArray * option_txt;
	public:
		Menu();
		Menu(dxManager * a_dxMgr,char*,char*);
		~Menu();
		void setParam(float width,float height,float a_x, float a_y);
		void Draw();
		int update(inputData * input, int now);
		void dialogueBox();
		void questDialogue(std::string filename);
		void storeMenu(std::string filename);
		int getselected(){return selected;}
};