#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include "Game.h"


class Menu
{
    public:
        Menu(int no_of_items,std::string * strings,int start_x,int start_y);
        void show(int alpha);
        std::string identify_event();
        virtual ~Menu();
        std::string clicked(int mouse_x,int mouse_y);
    protected:
    private:
        MenuItem * start;
        MenuItem * selected;
        SDL_Surface * background;
        Mix_Chunk * sound;
};

#endif // MENU_H
