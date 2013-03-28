#ifndef GOLI_H
#define GOLI_H

#include "SDL.h"
#include "SDL_image.h"
#include "const.h"

class Goli
{
    public:
        Goli(int,int,int,string,int,int,int);
        bool update();
        bool check_for_collision();
        bool check_collision(int,int);
        void get_pixel(int,int);
        virtual ~Goli();

    private:
        Uint8 r,g,b;
        int center_x;
        int center_y;
        int dir_x;
        int dir_y;
        int radius;
        SDL_Surface* image;
        int no_of_reflection;
        bool collide;
};


#endif // GOLI_H
