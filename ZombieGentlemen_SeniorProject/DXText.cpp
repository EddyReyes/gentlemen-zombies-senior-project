#include "DXText.h"
DXText::DXText()
{
	italic = bold = textToggle = imageOn = false;
	fontSize=0;
	box = NULL;
	font = NULL;
	fontColor = NULL;
	textBox = NULL;
}
DXText::DXText(dxManager * a_dxMgr)
{
	dxMgr = a_dxMgr;
	dialogText = new std::string;
	fontName = new std::string;
	box = NULL;
	fontColor = new D3DCOLOR;
	textBox = new RECT;

	// by default set font to arial
	fontSize = 20;
	bold = false;
	italic = false;
	setFontName("Arial");
	textToggle = true;
	imageOn = true;
}
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
	bold = false;
	italic = false;
	setFontName("Arial");
	textToggle = true;
	imageOn = true;
}
DXText::DXText(dxManager * a_dxMgr, LPDIRECT3DTEXTURE9 * img, D3DXIMAGE_INFO * imgInfo)
{
	dxMgr = a_dxMgr;
	dialogText = new std::string;
	fontName = new std::string;
	box = new HudImage(dxMgr, img, imgInfo);
	fontColor = new D3DCOLOR;
	textBox = new RECT;

	// by default set font to arial
	fontSize = 20;
	italic = false;
	bold = false;
	setFontName("Arial");
	textToggle = true;
	imageOn = true;
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
	if(box)
	{
		box->~HudImage();
		box = NULL;
	}

	// destroy text rectangle
	delete textBox;
	textBox = 0;
}

void DXText::setFont()
{
	// set weight for bolding of characters
	int weight = 0;
	if(bold)
		weight = FW_BOLD;
	else
		weight = FW_DONTCARE;

	//Create a D3DX font object
	D3DXCreateFont( *dxMgr->getDevice(),
					fontSize,			// SIZE
					0,
					weight,	// WEIGHT
					0,
					italic,		// Italic
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					PROOF_QUALITY,
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
void DXText::setImage(std::string filename)
{
	box->setImage(filename);
}
void DXText::toggleItalic()
{
	italic = !italic;
	setFont();
}

void DXText::toggleBold()
{ 
	bold = !bold;
	setFont();
}

void DXText::toggleImage(){imageOn = !imageOn;} 

void DXText::toggleText(){textToggle = !textToggle;}

void DXText::draw()
{
	if(imageOn)
	{
		if(box)
		box->draw();
	}
	
	if(textToggle)
	{
		font->DrawText(NULL, dialogText->c_str(),
			-1, textBox,
			DT_WORDBREAK, *fontColor);
	}
}
void DXText::setTextRectOffset(int offset)
{
	if(box)
	{
		textBox->top = (long)box->getYPosition() + offset;
		textBox->bottom = (long)(box->getYPosition() + (long)box->getHeight()) - offset;
		textBox->left = (long)box->getXPosition() + offset;
		textBox->right = (long)(box->getXPosition() + (long)box->getWidth()) - offset;
	}
}
bool DXText::setTextBoxParameters(float width, float height, float a_x, float a_y, int offset)
{
	if(box)
	{
		box->setParameters(width, height, a_x, a_y);
		setTextRectOffset(offset);
		return true;
	}
	else
	{
		setRect((int)a_y,(int)(a_y + height), (int)a_x, (int)(a_x + width));
	}
	return false;
}
HudImage* DXText::getimg(){return box;}
void DXText::loadFromTxtFile(char * filename)
{
	// open text file
	std::fstream file(filename);

	// check to see if text file is empty
	file.peek();
	if(file.eof())
		MessageBox(NULL,"invalid DXText parameters","Text Error",MB_OK);
	else
	{
		// if not load font name
		std::string fontName;
		char font[100];
		file.getline(font, 100);
		fontName.append(font);

		int a, r, g, b, offset;
		float width, height, x, y;

		file >> fontSize >> a >> r >> g >> b >> width >> height >> x >> y >> offset;

		if( a<0 || a > 255
			|| r<0 || r > 255
			|| g<0 || g > 255
			|| b<0 || b > 255)
		MessageBox(NULL,"invalid DXText color parameters","Text Error",MB_OK);

		if(fontSize <= 0)
			MessageBox(NULL,"invalid DXText size","Text Error",MB_OK);
		if(x < 0 || y < 0)
			MessageBox(NULL,"invalid DXText position","Text Error",MB_OK);
		if(width < 0 || height < 0)
			MessageBox(NULL,"invalid DXText width/height parameters","Text Error",MB_OK);
		if(offset < 0)
			MessageBox(NULL,"invalid offset","Text Error",MB_OK);

		*fontColor = D3DCOLOR_ARGB(a, r, g, b);
		setTextBoxParameters(width, height, x, y, offset);
	}
}