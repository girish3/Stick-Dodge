#include "Game.h"
#include "string"

using namespace std;

Game::Game()
{

}

int Game::stage_no;

SDL_Event Game::event;
TTF_Font* Game::font=NULL;              //font type will be lazy.ttf
bool Game::quit = false;

        int Game::x;
        int Game::y;                         //position of the stickman
        SDL_Surface* Game::screen;             // main screen on which all events happen(the game screen)
        SDL_Surface* Game::start_img;          // the game starts with this image
        SDL_Surface* Game::start_img_r;
        SDL_Surface* Game::start_img_l;
        SDL_Surface* Game::message1;
        SDL_Surface* Game::message;              // message to be printed on the screen
        Mykeys Game::keys;
        Mix_Music* Game::song;
        Mix_Chunk* Game::bullet_sound;
        Mix_Chunk* Game::die_sound;
        Mix_Chunk* Game::step_sound1;
        Mix_Chunk* Game::step_sound2;


gamestate Game::curr_state=MAINMENU;

action* Game::run = NULL;
action* Game::duck = NULL;
action* Game::jump_up = NULL;
action* Game::jump_forward = NULL;
action* Game::roll = NULL;
action* Game::flip = NULL;
action* Game::wall_flip = NULL;
action* Game::knee_slide = NULL;

SDL_Rect Game::box1;               // for upper screen
SDL_Rect Game::box2;                // for lower portion of the screen
bool Game::practice=false;           // determines whether user wants to practice or not
int Game::stage_completed;
ifstream Game::stage_file;
ofstream Game::stage_fileo;

Game::~Game()
{
    //dtor
}

void Game::init()
{
    x=SCREEN_WIDTH/2-92;                            // initializing the position of the stickman
    y=SCREEN_HEIGHT-183;

    start_img_r=load_image("stand_r.png");
    start_img_l=load_image("stand_l.png");
    //background = load_image("image1.jpg");
    start_img=start_img_r;
    keys.down = false;
    keys.up   = false;
    keys.left = false;
    keys.right= false;
    keys.D = false;
    keys.E = false;
    keys.F = false;
    box1.x=0;
    box1.y=100;
    box1.h=SCREEN_HEIGHT-100;
    box1.w=SCREEN_WIDTH;
    box2.x=0;
    box2.y=0;
    box2.h=100;
    box2.w=SCREEN_WIDTH;

    //int color = SDL_MapRGB(screen->format,0xFF,0xFF,0xFF);
    fill_white();
    apply_surface(x,y,start_img,screen,NULL);                         // apply the start_img here dont forgetS
    //pixel=(int *)screen->pixels;

}

void Game::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
    {
        //Holds offsets
        SDL_Rect offset;
        //Get offsets
        offset.x = x;
        offset.y = y;
        //Blit
        SDL_BlitSurface( source, clip, destination, &offset );
    }

SDL_Surface* Game::load_image(string filename)
{

    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    //If the image loaded
    if( loadedImage != NULL )
        {
            //Create an optimized image
            optimizedImage = SDL_DisplayFormat( loadedImage );
            //Free the old image
            SDL_FreeSurface( loadedImage );
        }

    //If the image was optimized just fine
    if( optimizedImage != NULL )
    {
        //Map the color key
        Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF );
        //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
     }

  return optimizedImage;
}

void Game::fill_white()
{
    box1.x=0;
    box1.y=100;
    box1.h=SCREEN_HEIGHT-100;
    box1.w=SCREEN_WIDTH;
    //apply_surface(0,0,background,screen,NULL);

    SDL_FillRect(Game::screen,&box1,SDL_MapRGB(Game::screen->format,0xFF,0xFF,0xFF));
}

void Game::fill_top()
{
    box1.x=0;
    box1.y=0;
    box1.h=100;
    box1.w=SCREEN_WIDTH;

    SDL_FillRect(Game::screen,&box1,SDL_MapRGB(Game::screen->format,0xFF,0xFF,0xFF));
}

void Game::set_gamestate(std::string act)
{
    if(act=="Exit")
        curr_state=QUIT;
    else if(act=="New Game")
        curr_state=NEWGAME;
    else if(act=="Resume")
        curr_state = GAMEPLAY;
    else if(act=="Main Menu")
        curr_state = MAINMENU;
    else if(act=="Practice")
    {
        curr_state = GAMEPLAY;
        practice=true;
    }
    else if(act=="LEVEL 1")
        {
            Game::stage_no=1;
            curr_state = GAMEPLAY;
        }

    else if(act=="LEVEL 2")
        {
            if(stage_completed>1)
               Game::stage_no=2;
            else
                Game::stage_no=0;
            curr_state = GAMEPLAY;
        }
    else if(act=="LEVEL 3")
        {
            if(stage_completed>2)
              Game::stage_no=3;
            else
               Game::stage_no=0;
            curr_state = GAMEPLAY;
        }
    else if(act=="LEVEL 4")
        {
            if(stage_completed>3)
              Game::stage_no=4;
            else
               Game::stage_no=0;
            curr_state = GAMEPLAY;
        }
    else if(act=="LEVEL 5")
        {
            if(stage_completed>4)
              Game::stage_no=5;
            else
               Game::stage_no=0;
            curr_state = GAMEPLAY;
        }
    else if(act=="LEVEL 6")
        {
            if(stage_completed>5)
              Game::stage_no=6;
            else
               Game::stage_no=0;
            curr_state = GAMEPLAY;
        }
    else if(act=="LEVEL 7")
        {
            if(stage_completed>6)
              Game::stage_no=7;
            else
               Game::stage_no=0;
            curr_state = GAMEPLAY;
        }
    else if(act=="LEVEL 8")
        {
            if(stage_completed>7)
              Game::stage_no=8;
            else
               Game::stage_no=0;
            curr_state = GAMEPLAY;
        }


    else if(act=="RANDOM LEVEL(for fun)")
        {
                  Game::stage_no=9;
                  curr_state = GAMEPLAY;
        }
    else if(act=="Controls")
        curr_state=CONTROLS;
   // else if(act=="play again")
   //     curr_state = GAMEPLAY;
}

void Game::free_everything()
{
    SDL_free(message);
    SDL_free(screen);
    SDL_free(start_img);
    SDL_free(start_img_l);
    SDL_free(start_img_r);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();         //implement this function and use at the end to free all surfaces and other resources
    Mix_FreeMusic(song);
    Mix_FreeChunk(bullet_sound);
    Mix_FreeChunk(die_sound);
    Mix_FreeChunk(step_sound1);
    Mix_FreeChunk(step_sound2);
    //Mix_FreeChunk();
    Mix_CloseAudio();

 }

 int Game::stage_read()
 {
     string line;
     Game::stage_file.open("libstdc.dll");
     getline(Game::stage_file,line);
     stage_file.close();
     return atoi(line.c_str());
 }

 void Game::stage_write(int stage_level)
 {
    // string line;
     Game::stage_fileo.open("libstdc.dll");
     stage_fileo << stage_level;
     stage_fileo.close();

 }

int Game::score_read()
 {
     string line;
     Game::stage_file.open("sm.dll");
     getline(Game::stage_file,line);
     stage_file.close();
     return atoi(line.c_str());
 }

void Game::score_write(int score)
 {
    // string line;
     Game::stage_fileo.open("sm.dll");
     stage_fileo << score;
     stage_fileo.close();

 }
