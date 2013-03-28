#ifndef STAGE_H
#define STAGE_H
#include "Game.h"
#include "const.h"
#include "LinkedList.h"
#include "timer.h"
#include "Node.h"
#include "MenuItem.h"
#include "Menu.h"
#include<fstream>

using namespace std;

class Stage: public Game
{
    public:
        Stage();
        static int start(string filename);
        static bool get_event();
        static void render_image();
        static void render_golis();
        static void create_golis();
        static bool check_collision();
        static void do_all(action*,int,bool,int);
        static void initialize(std::string filename);
        static void do_wall_flip(bool);
        static void close();
        static bool goli_part();
        virtual ~Stage();
        static Menu * collision_menu;
        static void countdown(string filename);
        static bool play_again;           // flag for countdown after 'play again' is clicked
        static bool random_stage;
        static void create_random_golis();
        static void render_random_golis();
        static bool check_random_collision();
        static goliyan bullet[no_of_bullets];
        static int score;                  // score of the random stage

    protected:

    private:
        static bool stance;
       // static SDL_Event event;
        //static Bullet * bullet;
        static LinkedList active_bullets;
        static LinkedList inactive_bullets;
        static bool collision;
        static int i;
        static int no_of_active_bullets;
        static int no_of_inactive_bullets;
        static timer mytimer;
        static Menu * stage_menu;
        static bool start_countdown;
        static bool run_on;
        static int height[7];          // height for the expert level (random stage)
        static int speed[5];           // random speed for the random stage
        static int total;              // to count bullets in the random stage
        static char number[4];          // same as total but type is char(for printing)
};

#endif // STAGE_H
