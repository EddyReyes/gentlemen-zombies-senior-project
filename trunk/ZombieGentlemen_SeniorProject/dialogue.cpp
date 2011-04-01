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
Dialogue::~Dialogue()
{
	
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
void Dialogue::setFontColor(int a, int r, int g, int b)
{
	*fontColor = D3DCOLOR_ARGB(a, r, g, b);
	setFont();
}
void Dialogue::setDialogue(std::string text)
{
	
}
void Dialogue::setRect(int top, int bottom, int left, int right)
{
	// create a rectangle to indicate where on the screen it should be drawn
	RECT rct;
	rct.left = 150;
	rct.right = rct.left+300;
	rct.top = 240;
	rct.bottom = rct.top +120;
}
void Dialogue::toggleItalic(){ italic = italic?false:true; }
void Dialogue::draw()
{
	dxMgr->beginRender();

	dxMgr->endRender();
}