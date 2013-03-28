#ifndef MENUITEM_H
#define MENUITEM_H

//#include<string>
#include "Game.h"
#include "const.h"


class MenuItem
{
    public:
        MenuItem(int,int,int,int,std::string);
        virtual ~MenuItem();
        bool checkBounds(int posX, int posY);
        void show();
        void set_text_color(int r,int g,int b);
        std::string text;
        MenuItem * next;
        MenuItem * previous;

    protected:
    private:
        int x,y;
        int width,height;
        SDL_Color text_color;

};

#endif // MENUITEM_H
