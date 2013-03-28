#ifndef GAME_H
#define GAME_H

#include "const.h"
#include "SDL_mixer.h"
#include<fstream>

class Game
{
    public:
        Game();
        static void init();
        static SDL_Surface* load_image(string);
        static void apply_surface(int,int,SDL_Surface*,SDL_Surface*,SDL_Rect*);
        static void free_everything();
        //static void fill_bg_bottom();
        //static void fill_bg_top();
        static void fill_white();
        static void fill_top();
        static void set_gamestate(std::string act);
        virtual ~Game();

        //following are public fields
        static int stage_no;
        static SDL_Surface* screen;             // main screen on which all events happen(the game screen)
        static SDL_Surface* message1;
        static int x;
        static int y;                         //position of the stickman
        static Mykeys keys;                       // struct to store the events
        static SDL_Surface* start_img;          // the game starts with this image
        static SDL_Surface* start_img_r;
        static SDL_Surface* start_img_l;
        static SDL_Surface* message;              // message to be printed on the screen
        static TTF_Font* font;
        static Mix_Music* song;
        static Mix_Chunk* bullet_sound;
        static Mix_Chunk* die_sound;
        static Mix_Chunk* step_sound1;
        static Mix_Chunk* step_sound2;
        static bool quit;
        static action* run;
        static action* duck;
        static action* jump_up;
        static action* flip;
        static action* roll;
        static action* jump_forward;
        static action* wall_flip;
        static action* knee_slide;
        static SDL_Event event;
        static gamestate curr_state;
        static SDL_Rect box1;
        static SDL_Rect box2;
        static bool practice;
        static int stage_read();
        static int score_read();
        static void score_write(int);
        static void stage_write(int);
        static int stage_completed;
        static ifstream stage_file;
        static ofstream stage_fileo;

    protected:
    private:


};

#endif // GAME_H
