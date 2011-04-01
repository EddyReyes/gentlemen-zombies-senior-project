//Dialogue class
#include <string.h>
#include "HudImage.h"
#include "dxManager.h"

class Dialogue
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

	public:
		Dialogue(dxManager * a_dxMgr, std::string filename);
		~Dialogue();
		void setFont();
		void setFontName(std::string a_fontName);
		void setFontSize(int a_size);
		void setFontColor();
		void setImage();
		void setDialogue();
		void setRect(int top, int bottom, int left, int right);
		void toggleItalic();
};