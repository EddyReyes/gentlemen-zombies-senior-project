#pragma once
#include <string.h>
#include "HudImage.h"
#include "dxManager.h"

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
		DXText(dxManager * a_dxMgr, std::string filename);
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
		void setSize(float width, float height);
		void setPosition(int a_x, int a_y);
		void setTextRectOffset(int offset);
		void setTextBoxParameters(float width, float height, int a_x, int a_y, int offset);

		void setImage(std::string filename);
};