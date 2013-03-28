#include "Menu.h"


Menu::Menu(int no_of_items,std::string * strings,int start_x,int start_y)
{
    sound = Mix_LoadWAV("menu.wav");

    int x = start_x;
    int y = start_y;

    start = new MenuItem(x,y,100,50,strings[0]);
    y=y+50;
    start->previous = NULL;
    MenuItem * temp1 = start;
    MenuItem * temp2 = start;

    int i=1;
    while(i<no_of_items)
    {
        temp2 = new MenuItem(x,y,100,50,strings[i]);
        temp1->next = temp2;
        temp2->previous = temp1;
        temp1 = temp2;
        y=y+50;
        i++;
    }

    temp2->next = NULL;
    selected = start;
    selected->set_text_color(255,255,255);

    background = Game::load_image("libFLAC.dll");
    if(start_x<150)
     background = Game::load_image("controls.JPG");
}

void Menu::show(int alpha)
{
    SDL_SetAlpha(background,SDL_SRCALPHA,alpha);

    if(alpha!=250)
        Game::apply_surface(0,0,background,Game::screen,NULL);
    else
        {
            SDL_FillRect(Game::screen,&Game::screen->clip_rect,SDL_MapRGB(Game::screen->format,0x00,0x00,0x00));
            Game::apply_surface(0,0,background,Game::screen,NULL);
        }

    MenuItem * temp = start;
    while(temp!=0)
    {
        temp->show();
        temp = temp->next;
    }
    SDL_Flip(Game::screen);
}

std::string Menu::clicked(int mouse_x,int mouse_y)
{
    MenuItem * next = start;
    while(next!=0)
    {
        if(next->checkBounds(mouse_x,mouse_y))
            return next->text;
        next=next->next;
    }
    return "None";

}

std::string Menu::identify_event()
{
    std::string temp;
    while(1)
    {
        while(SDL_PollEvent(&(Game::event)))
        {
            if(Game::event.type==SDL_QUIT)
                return "Exit";

            if(Game::event.type == SDL_KEYDOWN)
            {
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if(selected->previous!=NULL)
                        {
                            Mix_PlayChannel(-1,sound,0);

                            selected->set_text_color(150,150,150);
                            selected->show();
                            selected = selected->previous;
                            selected->set_text_color(255,255,255);
                            selected->show();
                            SDL_Flip(Game::screen);
                        }
                        break;

                    case SDLK_DOWN:
                        if(selected->next!=NULL)
                        {
                            Mix_PlayChannel(-1,sound,0);

                            selected->set_text_color(150,150,150);
                            selected->show();
                            selected = selected->next;
                            selected->set_text_color(255,255,255);
                            selected->show();
                            SDL_Flip(Game::screen);
                        }
                        break;

                    case SDLK_RETURN:
                        return selected->text;

                    default :
                        break;
                }
            }
        }
    }
}

Menu::~Menu()
{

}
