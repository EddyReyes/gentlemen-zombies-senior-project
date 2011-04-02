//DXText class
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
		bool toggle;
		

	public:
		DXText(dxManager * a_dxMgr, std::string filename);
		~DXText();
		void setFont();
		void setFontName(std::string a_fontName);
		void setFontSize(int a_size);
		void setFontColor(int a, int r, int g, int b);
		//void setImage(std::string a_fontName);
		void setDialog(std::string text);
		void setRect(int a_top, int a_bottom, int a_left, int a_right);
		void setTextToArial();
		void toggleItalic();
		void toggleBold();
		void draw();
};