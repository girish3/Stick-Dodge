#ifndef CONST_H

#define CONST_H
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "action.h"
#include "SDL_ttf.h"
#include "Goli.h"


using namespace std;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int NO_OF_STAGES = 9;
const int no_of_bullets = 4;         // for the random stage
extern SDL_Color txtcolor;


class Goli;

enum gamestate{GAMEPLAY,MAINMENU,QUIT,NEWGAME,CONTROLS};

typedef struct
{
    bool right,left,up,down,D,W,F,E;
}Mykeys;

typedef struct
{
    Goli * gol;
    int time;
}Bullet;

typedef struct
{
    Goli * gol;
    bool exist;
}goliyan;


#endif
