#include "Game.h"
#include "const.h"
#include "Stage.h"

Goli::Goli(int centerx,int centery,int radius,string filename,int dirx,int diry,int no_of_reflection)
{
    this->center_x=centerx;
    this->center_y=centery;
    this->radius=radius;
    this->dir_x=dirx;
    this->dir_y=diry;
    this->image=Game::load_image(filename);
    this->no_of_reflection=no_of_reflection;
    this->collide=false;
}

bool Goli::update()
{


    if(center_x+radius+dir_x>=SCREEN_WIDTH || center_x-radius+dir_x<=0)
    {
        center_x-=dir_x;
        dir_x=-dir_x;
        no_of_reflection--;
    }
    else
        center_x+=dir_x;

    if(center_y+radius+dir_y>=(SCREEN_HEIGHT-5) || center_y-radius+dir_y<=0)
    {
        center_y-=dir_y;
        dir_y=-dir_y;
        no_of_reflection--;
    }
    else
        center_y+=dir_y;

    if(no_of_reflection<0)
        return false;

    Game::apply_surface(center_x-(radius),center_y-(radius),image,Game::screen,NULL);
    return true;
}

bool Goli::check_for_collision()          // checks for all bullets
{
    int i,j;
    i=0;
    j=0;

    if(dir_y==0)
    {
        while(i!=dir_x)
        {
            if(center_x+i+radius>=SCREEN_WIDTH || center_x+i-radius<=0)
                return false;

            if(check_collision(center_x+i,center_y))
                break;
            i+=(dir_x>0)?(1):(-1);
        }
        if(i==0)
            check_collision(center_x,center_y);
    }

    if(collide)
    {
        Mix_PlayChannel(0,Game::die_sound,0);
        Game::apply_surface(center_x+i-radius,center_y-radius,image,Game::screen,NULL);
        SDL_Flip(Game::screen);
        SDL_Delay(500);

        if(Game::curr_state==GAMEPLAY)
              {
                  Stage::play_again=true;
                  Mix_PauseMusic();
                  Game::fill_top();
              }


        return true;
    }
    return false;
}

bool Goli::check_collision(int centerx,int centery)  // checks for a specific bullet
{

    get_pixel(centerx-radius-1,centery);          //left
    if(b==0x00)
        collide=true;                                // if collision then return true

    get_pixel(centerx,centery-radius-1);          //top
    if(b==0x00)
        collide=true;                                // if collision then return true

    get_pixel(centerx,centery+radius+1);           //bottom
    if(b==0x00)
        collide=true;                               // if collision then return true

    get_pixel(centerx+radius+1,centery);          //right
    if(b==0x00)
        collide=true;                               // if collision then return true

    if(collide==true)
    {
        //Game::message=TTF_RenderText_Solid(Game::font,"collision occured",txtcolor);
        //Game::apply_surface(10,10,Game::message,Game::screen,NULL);
        //SDL_Flip(Game::screen);
        return true;
    }
    return false;
}


void Goli::get_pixel(int x_cord,int y_cord)
{
   Uint32 *pixel =(Uint32 *) Game::screen->pixels;
   SDL_GetRGB(pixel[(y_cord*SCREEN_WIDTH)+x_cord],Game::screen->format,&r,&g,&b);

}

Goli::~Goli()
{
    //delete this;
}
