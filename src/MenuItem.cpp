#include "MenuItem.h"

MenuItem::MenuItem(int x, int y, int width, int height,std::string text)
{
	this->x = x;
	this->y = y;

	this->width = width;
	this->height = height;

	this->text = text;

	this->next = 0;

	this->text_color = {150,150,150};
}

MenuItem::~MenuItem()
{
    if (next !=0)
	{
		delete next;
	}
}

bool MenuItem::checkBounds(int posX, int posY)
{
	if ( posX >= x && posX <= x+width)
	{
		if ( posY >= y && posY <= y+height)
		{
		        return true;
		}
	}
	return false;
}

void MenuItem::set_text_color(int r,int g,int b)
{
    text_color.r=r;
    text_color.g=g;
    text_color.b=b;
}

void MenuItem::show()
{
    Game::message=TTF_RenderText_Solid(Game::font,text.c_str(),text_color);
    Game::apply_surface(x,y,Game::message,Game::screen,NULL);
}
