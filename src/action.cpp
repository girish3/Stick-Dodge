#include "const.h"
#include "Game.h"
#include "Stage.h"

// all action class functions and fields

action::action(string filename,int width,int height,int offset,int total)
{
    this->width=width;               // check to see if 'this'(ptr) works
    this->height=height;             // is 'this' the ptr of function or class ? check it out
    this->offset=offset;
    this->total=total;
    this->image_seq=Game::load_image(filename);
}

int action::next=1;

action::~action()
{
    SDL_FreeSurface(image_seq);
}

void action::apply_next_right()
{
    SDL_Rect box;
    box.x=(next-1)*width;
    box.y=0;
    box.w=width;
    box.h=height/2;

    Game::x+=offset;
    if((Game::x+width)>=SCREEN_WIDTH)
        Game::x=SCREEN_WIDTH-width;



    Game::fill_white();
    Game::apply_surface(Game::x,Game::y,image_seq,Game::screen,&box);

    if(next<total)
        next++;
    else
        next=1;
}

void action::apply_next_left()
{
    SDL_Rect box;
    box.x=(total-next)*width;
    box.y=height/2;
    box.w=width;
    box.h=height/2;

    Game::x-=offset;
    if(Game::x<=0)
        Game::x=0;

    Game::fill_white();
    Game::apply_surface(Game::x,Game::y,image_seq,Game::screen,&box);

    if(next<total)
        next++;
    else
        next=1;

}

void action::reset()
{
    next=1;
}
