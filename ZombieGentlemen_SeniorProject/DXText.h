#pragma once
#include <string.h>
#include "HudImage.h"
#include "dxManager.h"
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <string.h>

class DXText
{
	private:
		std::string * dialogText;
		std::string * fontName;
		HudImage * box;
		ID3DXFont * font;
		dxManager * dxMgr;
		D3DCOLOR * fontColor;
		RECT * textBox;
		int fontSize;
		bool italic;
		bool bold;
		bool textToggle;
		bool imageOn;

	public:
		DXText();
		DXText(dxManager * a_dxMgr);
		DXText(dxManager * a_dxMgr, std::string filename);
		DXText(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * img, D3DXIMAGE_INFO * imgInfo);
		~DXText();
		void setFont();
		void setFontName(std::string a_fontName);
		void setFontSize(int a_size);
		void setFontColor(int a, int r, int g, int b);
		void textInfo(std::string a_fontName, int a_size, D3DCOLOR a_textColor, std::string a_text);
		//void setImage(std::string a_fontName);
		void setDialog(std::string text);
		void setRect(int a_top, int a_bottom, int a_left, int a_right);
		void toggleItalic();
		void toggleBold();
		void toggleImage();
		void toggleText();
		void draw();
		void setTextRectOffset(int offset);
		bool setTextBoxParameters(float width, float height, float a_x, float a_y, int offset);
		void setImage(std::string filename);
		HudImage* getimg();
		void loadFromTxtFile(std::string filename);

		int getTextBoxWidth();
		int getTextBoxHeight();
		int getTextBoxXPos();
		int getTextBoxYPos();
};