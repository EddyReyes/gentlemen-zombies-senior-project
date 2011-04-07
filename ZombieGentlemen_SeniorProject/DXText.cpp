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
	textToggle = true;
	imageOn = true;
	width = 0;
	height = 0;
}

DXText::~DXText()
{
	// destroy strings
	dialogText->~basic_string();
	delete dialogText;
	dialogText = 0;
	fontName->~basic_string();
	delete fontName;
	fontName = 0;

	// destroy font
	font->Release();
	font = NULL;

	//destroy font color
	delete fontColor;
	fontColor = NULL;

	// destroy text box image
	box->~HudImage();
	box = NULL;

	// destroy text rectangle
	delete textBox;
	textBox = 0;
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
	// indicate where on the screen it should draw text
	textBox->bottom = a_bottom;
	textBox->top = a_top;
	textBox->left = a_left;
	textBox->right = a_right;
}

void DXText::toggleItalic(){ italic = !italic;}

void DXText::toggleBold(){ bold = !bold;}

void DXText::toggleImage(){imageOn = !imageOn;} 

void DXText::toggleText(){textToggle = !textToggle;}

void DXText::draw()
{
	if(imageOn)
	{
		box->draw();
	}
	
	if(textToggle)
	{
		font->DrawText(NULL, dialogText->c_str(),
			-1, textBox,
			DT_WORDBREAK, *fontColor);
	}
}
void DXText::setPosition(int a_x, int a_y)
{
	box->setPosition(a_x, a_y);
}
void DXText::setSize(float a_width, float a_height)
{
	width = a_width;
	height = a_height;
	D3DXIMAGE_INFO * tempInfo = box->getImageInfo();
	box->setWidthScale(width/(float)tempInfo->Width);
	box->setHeightScale(height/(float)tempInfo->Height);
	box->scaleCustom();
}
void DXText::setTextRectOffset(int offset)
{
	textBox->top = box->getYPosition() + offset;
	textBox->bottom = (box->getYPosition() + box->getHeight()) - offset;
	textBox->left = box->getXPosition() + offset;
	textBox->right = (box->getXPosition() + box->getWidth()) - offset;
}
void DXText::setTextBoxParameters(float width, float height, int a_x, int a_y, int offset)
{
	setSize(width, height);
	setPosition(a_x, a_y);
	setTextRectOffset(offset);
}