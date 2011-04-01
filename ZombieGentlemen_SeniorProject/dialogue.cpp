#include "dialogue.h"



// when you need pd3ddevice use *dxMgr->getDevice()

Dialogue::Dialogue(dxManager * a_dxMgr, std::string filename)
{
	dxMgr = a_dxMgr;
	dialogText = new std::string;
	fontName = new std::string;
	box = new HudImage(dxMgr, filename);
	fontColor = new D3DCOLOR;
	textBox = new RECT;

	// by default set font to arial
	fontSize = 20;
	italic = false;
	setFontName("Arial");
	toggle = true;
	
}
void Dialogue::setFont()
{
	//Create a D3DX font object
	D3DXCreateFont( *dxMgr->getDevice(),
					fontSize,			// SIZE
					0,
					FW_BOLD,	// WEIGHT
					0,
					italic,		// Italic
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_DONTCARE,
					TEXT(fontName->c_str()),
					&font );
}
void Dialogue::setFontName(std::string a_fontName)
{
	*fontName = a_fontName;
	setFont();
}
void Dialogue::setFontSize(int a_size)
{
	fontSize = a_size;
	setFont();
}
// set font color using D3DCOLOR_ARGB(a, r, g, b)
//*fontColor = D3DCOLOR_ARGB(a, r, g, b) 