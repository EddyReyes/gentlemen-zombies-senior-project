#include "DXText.h"

DXText::DXText(dxManager * a_dxMgr, std::string filename)
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

DXText::~DXText()
{
	dialogText->~basic_string();
	delete dialogText;
	fontName->~basic_string();
	delete fontName;
	font->Release();
	delete fontColor;
	box->~HudImage();
	delete box;
	delete textBox;
}

void DXText::setFont()
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

void DXText::setFontName(std::string a_fontName)
{
	*fontName = a_fontName;
	setFont();
}

void DXText::setFontSize(int a_size)
{
	fontSize = a_size;
	setFont();
}

void DXText::setFontColor(int a, int r, int g, int b)
{
	*fontColor = D3DCOLOR_ARGB(a, r, g, b);
	setFont();
}

void DXText::setDialog(std::string a_text)
{
	*dialogText = a_text;
}

void DXText::textInfo(std::string a_fontName, int a_size, D3DCOLOR a_textColor, std::string a_text)
{
	setFontName(a_fontName);
	setFontSize(a_size);
	*fontColor = a_textColor;
	setDialog(a_text);
}

void DXText::setRect(int a_top, int a_bottom, int a_left, int a_right)
{
	// indicate where on the screen it should be drawn
	textBox->bottom = a_bottom;
	textBox->top = a_top;
	textBox->left = a_left;
	textBox->right = a_right;
}

void DXText::toggleItalic(){ italic = italic?false:true;}

void DXText::toggleBold(){ bold = bold?false:true;}

void DXText::draw()
{
	font->DrawText(NULL, dialogText->c_str(),
					-1, textBox,
					DT_WORDBREAK, *fontColor);
}