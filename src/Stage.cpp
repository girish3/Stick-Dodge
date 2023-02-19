#include "Stage.h"
#include "action.h"
#include "string"
#include "sstream"

using namespace std;

Stage::Stage() {

}

Stage::~Stage() {
    //dtor
}

bool Stage::stance = true;
//SDL_Event Stage::event;
//Bullet * Stage::bullet=NULL;
bool Stage::collision = false;
int Stage::i;
timer Stage::mytimer;
int Stage::no_of_active_bullets;
int Stage::no_of_inactive_bullets;
LinkedList Stage::active_bullets;
LinkedList Stage::inactive_bullets;
Menu *Stage::stage_menu;
Menu *Stage::collision_menu;
bool Stage::play_again = false;
bool Stage::start_countdown = true;
bool Stage::run_on = false;
bool Stage::random_stage = false;
int Stage::speed[5] = {5, 10, 15, 20, 25};
int Stage::height[7] = {52, 55, 70, 100, 130, 150, 170};
goliyan Stage::bullet[no_of_bullets];
int Stage::total = 0;
char Stage::number[4];
int Stage::score;


void Stage::initialize(std::string filename) {
    string line;

    if (filename == "1")
        stage_file.open("libog-0.dll");
    else if (filename == "2")
        stage_file.open("libweb-1.dll");
    else
        stage_file.open("zlib2.dll");

    getline(stage_file, line);
    no_of_inactive_bullets = atoi(line.c_str());
    //no_of_inactive_bullets=5;
    no_of_active_bullets = 0;

    int parameters[6];
    int j;
    while (stage_file) {
        j = 0;
        getline(stage_file, line);                   //read the line from file

        char *lin = new char[line.size() +
                             1];        //converting string to a char * to pass to strtok(line.c_str() gives a const char *)
        copy(line.begin(), line.end(), lin);
        lin[line.size() + 1] = '\0';

        char *p = strtok(lin, " ");
        while (p) {
            parameters[j] = atoi(p);
            p = strtok(NULL, " ");
            j++;
        }

        delete lin;             //set breakpoint here

        Bullet temp;

        if (parameters[0] <= 10)
            temp.gol = new Goli(parameters[0], SCREEN_HEIGHT - parameters[1], 9, "ball.png", parameters[2],
                                parameters[3], parameters[4]);
        else
            temp.gol = new Goli(SCREEN_WIDTH - parameters[0], SCREEN_HEIGHT - parameters[1], 9, "ball.png",
                                -parameters[2], -parameters[3], parameters[4]);

        temp.time = parameters[5];
        inactive_bullets.add(temp);
    }
    stage_file.close();

    /*
    int xcenter[5]={5,1190,5,5,1190};
    int ycenter[5]={450,300,500,590,450};
    int xdir[5]={20,-20,20,5,-40};
    int ydir[5]={0,0,0,0,0};
    int reflections[5]={1,2,1,1,2};
    int time_of_origin[5]={1000,2000,2000,3000,5000};
    */

    /*
    int xcenter[2]={5,5};
    int ycenter[2]={450,500};
    int xdir[2]={20,20};
    int ydir[2]={0};
    int reflections[2]={1,1};
    int time_of_origin[2]={1000,2000};
    */

    //bullet = new Bullet[no_of_bullets];
    /*
    int i=0;
    while(i<no_of_inactive_bullets)                                  //add all the bullets to inactive bullets queue
    {
        Bullet temp;
        temp.gol=new Goli(xcenter[i],ycenter[i],9,"ball.png",xdir[i],ydir[i],reflections[i]);
        temp.time = time_of_origin[i];
        inactive_bullets.add(temp);
        i++;
    }
    */

}

void Stage::close() {
    //stage_file.close();

    Node *current = active_bullets.returnhead();           //delete active bullets
    Node *temp;
    if (current != NULL)
        temp = current->getNext();
    while (current != NULL) {
        delete current;
        current = temp;
        if (current != NULL)
            temp = current->getNext();
    }
    active_bullets.set_null();

    current = inactive_bullets.returnhead();
    if (current != NULL)
        temp = current->getNext();
    while (current != NULL) {
        delete current;
        current = temp;
        if (current != NULL)
            temp = current->getNext();
    }
    inactive_bullets.set_null();

    no_of_active_bullets = 0;
    no_of_inactive_bullets = 0;
}

bool Stage::get_event() {
    if (event.type == SDL_QUIT) {
        //QUIT THE PROGRAM
        return false;
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                if (!stance && x >= 100)
                    x = x - 20;
                stance = true;
                keys.right = true;
                //if(Mix_PausedMusic()==1)
                //    Mix_PlayMusic(running,-1);
                break;

            case SDLK_LEFT:
                if (stance && x <= (SCREEN_WIDTH - 239))
                    x = x + 20;
                stance = false;
                keys.left = true;
                //Mix_PlayChannel(-1,running,-1);
                // if(Mix_PausedMusic()==1)
                //     Mix_PlayMusic(running,-1);
                //Mix_PlayChannel(-1,Game::song,0);
                break;

            case SDLK_DOWN:
                keys.down = true;
                break;

            case SDLK_UP:
                keys.up = true;
                break;

            case SDLK_d:
                keys.D = true;
                break;

            case SDLK_w:
                keys.W = true;
                break;

            case SDLK_f:
                keys.F = true;
                break;

            case SDLK_e:
                keys.E = true;
                break;

            case SDLK_ESCAPE:
                mytimer.pause();
                stage_menu->show(255);
                Game::set_gamestate((stage_menu->identify_event()));

                if (Game::curr_state == GAMEPLAY) {
                    mytimer.unpause();
                    Game::fill_top();
                } else
                    practice = false;

                break;

            default:
                break;
        }
    } else if (event.type == SDL_KEYUP)     // block for handling event
    {
        action::reset();

        switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                keys.right = false;
                // if(Mix_PlayingMusic()==1)
                //     Mix_PauseMusic();
                break;

            case SDLK_LEFT:
                keys.left = false;

                //  if(Mix_PlayingMusic()==1)
                //        Mix_PauseMusic();
                break;

            case SDLK_DOWN:
                keys.down = false;
                break;

            case SDLK_UP:
                keys.up = false;
                break;

            case SDLK_f:
                keys.F = false;
                break;

            case SDLK_w:
                keys.W = false;
                break;

            case SDLK_d:
                keys.D = false;
                break;

            case SDLK_e:
                keys.E = false;

            default:
                break;
        }

    }
    return true;
}

void Stage::render_image() {
    if (stance == true)                       // applying right image if stance is true
        start_img = start_img_r;
    else
        start_img = start_img_l;


    if (!keys.down && !keys.left && !keys.right && !keys.up) {
        Game::fill_white();
        apply_surface(x, y, start_img, screen, NULL);          // if no key is pressed apply the start image
    } else {
        switch (stance) {
            case true:

                if (keys.right && keys.F)                      //flip right
                {
                    do_all(flip, 13, true, 279 - 183);
                    x = x - 50;
                } else if (keys.right && keys.W)         // wall flip right
                {
                    if (x > (SCREEN_WIDTH - 270) && x < (SCREEN_WIDTH - 175)) {
                        do_wall_flip(true);
                        x = x - 40;
                    } else
                        keys.W = false;
                } else if (keys.right && keys.E)         // knee_slide right
                {
                    do_all(knee_slide, 21, true, 0);
                } else if (keys.up && keys.right)               // jump right
                {
                    do_all(jump_forward, 7, true, 220 - 183);
                } else if (keys.down && keys.right)               //Roll to right
                    do_all(roll, 8, true, 0);

                else if (keys.right)                         //Run to right
                {
                    run->apply_next_right();
                } else if (keys.down)                             //duck
                {
                    duck->apply_next_right();
                } else if (keys.up)                               //jump at the same place
                {
                    x = x + 50;
                    do_all(jump_up, 9, true, 278 - 183);
                    x = x - 50;
                }

                break;

            case false:

                if (keys.left && keys.F)                        //flip left
                {
                    do_all(flip, 13, false, 279 - 183);
                    x = x + 50;
                } else if (keys.left && keys.W)         // wall flip left
                {
                    if (x > (0) && x < (120)) {
                        do_wall_flip(false);
                        x = x + 70;
                    } else
                        keys.W = false;
                } else if (keys.left && keys.E)         // knee_slide left
                {
                    do_all(knee_slide, 21, false, 0);
                } else if (keys.up && keys.left)               // jump left
                {
                    do_all(jump_forward, 7, false, 220 - 183);
                } else if (keys.down && keys.left)                //Roll to left
                    do_all(roll, 8, false, 0);

                else if (keys.left)                             //Run to left
                    run->apply_next_left();

                else if (keys.down)                            //duck
                    duck->apply_next_left();

                else if (keys.up)                              //jump at the same place
                {
                    x = x - 50;
                    do_all(jump_up, 9, false, 278 - 183);
                    x = x + 50;
                }
                break;

        }
    }
}

void Stage::do_all(action *act, int limit, bool side, int shift_y)        //increase and decrease y by shift_y
{
    action::reset();
    y = y - shift_y;

    while (limit--) {
        if (side) {
            act->apply_next_right();

        } else {
            act->apply_next_left();

        }


        if (!practice) {
            if (!random_stage) {
                create_golis();                  // for  creating bullets
                render_golis();                  // for updating all bullets on the screen
            } else {
                create_random_golis();
                render_random_golis();
            }
        }

        if (limit)
            SDL_Delay(50);

        if (limit == 3) {
            Mix_PlayChannel(0, step_sound1, 0);
        }


        if (!practice) {
            if (!random_stage) {
                if (check_collision())            // checking for collision
                {
                    collision = true;

                    if (Stage::play_again)
                        break;

                    break;

                }
            } else {
                if (check_random_collision()) {
                    collision = true;

                    if (Stage::play_again)
                        break;

                    break;
                }
            }
        }
        SDL_Flip(screen);
    }

    y = y + shift_y;
}

int Stage::start(string filename) {
    fill_top();
    if (filename != "4")
        initialize(filename);
    else
        random_stage = true;

    score = score_read();

    string menuitems[] = {"Resume", "Main Menu"};
    stage_menu = new Menu(2, menuitems, 300, 300);
    menuitems[0] = "play again";
    //string menuit[] = {"play again","Main Menu"};
    collision_menu = new Menu(2, menuitems, 300, 300);

    if (play_again == true || practice == true)
        start_countdown = false;
    else
        start_countdown = true;

    if (start_countdown == true && Game::curr_state != MAINMENU)
        countdown(filename);

    play_again = false;

    init();

    if (random_stage) {
        for (i = 0; i < no_of_bullets; i++) {
            Stage::bullet[i].exist = false;
            Stage::bullet[i].gol = NULL;
        }
    }

    mytimer.start();
    mytimer.pause();

    while (1) {
        switch (Game::curr_state) {
            case QUIT:
                return 2;

            case GAMEPLAY:
                mytimer.unpause();
                while (Game::curr_state == GAMEPLAY) {
                    while (SDL_PollEvent(&(Game::event))) {
                        if (!get_event())              //sets the variables(up,down..etc) according to the events
                        {                             // returns false if X was clicked
                            quit = true;

                        }
                    }


                    render_image();                  // image rendering

                    if (!practice) {
                        if (goli_part()) {

                            Stage::collision_menu->show(255);

                            if (random_stage) {
                                char score_string[3];

                                message = TTF_RenderText_Solid(font, "Your score:", txtcolor);
                                apply_surface(600, 100, message, screen, NULL);
                                //itoa(total, score_string, 10);
                                ::sprintf(score_string, "%ld", total);
                                message = TTF_RenderText_Solid(font, score_string, txtcolor);
                                apply_surface(800, 100, message, screen, NULL);
                                total = 0;

                                SDL_Flip(screen);

                                message = TTF_RenderText_Solid(font, "Khel naa yaar", txtcolor);
                                apply_surface(600, 200, message, screen, NULL);
                            }
                            Game::set_gamestate(Stage::collision_menu->identify_event());

                            mytimer.stop();
                            //Mix_PauseMusic();
                            return 1;
                        }
                    }

                    SDL_Delay(50);

                    SDL_Flip(screen);

                    if (!practice) {
                        if (!random_stage) {
                            if (no_of_active_bullets == 0 && no_of_inactive_bullets == 0)     //stage cleared
                                return 0;
                        }                                                   //stage cleared
                    }
                }

            case MAINMENU:
                mytimer.stop();
                close();
                if (random_stage)
                    random_stage = false;
                return 3;                                       //quit to main menu
        }
    }
}

void Stage::create_golis() {
    while (no_of_inactive_bullets > 0) {
        Bullet temp = inactive_bullets.getfirstdata();

        if (temp.time >= mytimer.get_ticks())
            break;

        active_bullets.add(temp);
        inactive_bullets.deque();
        no_of_active_bullets++;
        no_of_inactive_bullets--;
        Mix_PlayChannel(0, bullet_sound, 0);
    }

}

void Stage::render_golis() {
    Node *current = active_bullets.returnhead();
    Node *previous = NULL;
    Node *nex = NULL;
    if (current != NULL)
        nex = current->getNext();

    while (current != NULL) {
        Bullet temp = current->getData();
        if (!(temp.gol->update())) {
            active_bullets.remove(previous, current);
            no_of_active_bullets--;
            current = nex;

            if (current != NULL)
                nex = current->getNext();
            //previous=current;
            //current = current->getNext();
        } else {
            previous = current;
            current = nex;
            if (current != NULL)
                nex = current->getNext();
        }

    }

}

bool Stage::check_collision() {
    Node *current = active_bullets.returnhead();
    while (current != NULL) {
        Bullet temp = current->getData();
        if (temp.gol->check_for_collision())
            return true;
        current = current->getNext();
    }

    return false;
}

void Stage::do_wall_flip(bool side) {
    int i = 5;
    action::reset();
    y = y - (400 - 183);
    Mix_PlayChannel(0, step_sound2, 0);

    while (i--) {

        if (side) {
            x = x + 30;
            Game::wall_flip->apply_next_right();
        } else {
            x = x - 30;
            Game::wall_flip->apply_next_left();
        }

        if (!practice) {
            if (!random_stage) {
                create_golis();                  // for  creating bullets
                render_golis();                  // for updating all bullets on the screen
            } else {
                create_random_golis();
                render_random_golis();
            }
        }

        SDL_Flip(screen);
        SDL_Delay(50);

        if (!practice) {
            if (!random_stage) {
                if (check_collision())            // checking for collision
                {
                    collision = true;

                    if (Stage::play_again)
                        break;

                    break;

                }
            } else {
                if (check_random_collision()) {
                    collision = true;

                    if (Stage::play_again)
                        break;

                    break;
                }
            }
        }

    }

    i = 7;


    if (!collision) {
        while (i--) {

            if (side) {
                x = x - 15;
                Game::wall_flip->apply_next_right();
            } else {
                x = x + 15;
                Game::wall_flip->apply_next_left();
            }

            if (!practice) {
                if (!random_stage) {
                    create_golis();                  // for  creating bullets
                    render_golis();                  // for updating all bullets on the screen
                } else {
                    create_random_golis();
                    render_random_golis();
                }
            }

            SDL_Flip(screen);
            SDL_Delay(50);

            if (!practice) {
                if (!random_stage) {
                    if (check_collision())            // checking for collision
                    {
                        collision = true;

                        if (Stage::play_again)
                            break;

                        break;

                    }
                } else {
                    if (check_random_collision()) {
                        collision = true;

                        if (Stage::play_again)
                            break;

                        break;
                    }
                }
            }

        }
    }

    i = 7;
    Mix_PlayChannel(0, step_sound1, 0);

    if (!collision) {
        while (i--) {

            if (side) {
                Game::wall_flip->apply_next_right();
            } else {
                Game::wall_flip->apply_next_left();
            }

            if (!practice) {
                if (!random_stage) {
                    create_golis();                  // for  creating bullets
                    render_golis();                  // for updating all bullets on the screen
                } else {
                    create_random_golis();
                    render_random_golis();
                }
            }

            SDL_Flip(screen);
            SDL_Delay(50);

            if (!practice) {
                if (!random_stage) {
                    if (check_collision())            // checking for collision
                    {
                        collision = true;

                        if (Stage::play_again)
                            break;

                        break;

                    }
                } else {
                    if (check_random_collision()) {
                        collision = true;

                        if (Stage::play_again)
                            break;

                        break;
                    }
                }
            }


        }
    }

    y = y + (400 - 183);
}

bool Stage::goli_part() {
    if (!random_stage) {
        create_golis();                  // for  creating bullets

        if (collision == true) {
            collision = false;
            close();
            return true;              //collision occured
        }

        if (check_collision())            // checking for collision
        {
            close();
            return true;
        }

        render_golis();                  // for updating all bullets on the screen

        return false;
    } else {
        create_random_golis();

        if (collision == true) {
            collision = false;
            return true;
        }

        if (check_random_collision())
            return true;

        render_random_golis();

        return false;
    }
}

void Stage::countdown(string filename) {
    //bool check;
    int POSITION = 300;
    timer c_down;
    stringstream count;

    if (filename != "4")
        count << "stage " << filename << " begins in";
    else
        count << "random level begins in";

    SDL_Surface *number = TTF_RenderText_Solid(font, "2", txtcolor);

    message = TTF_RenderText_Solid(font, count.str().c_str(), txtcolor);

    fill_white();
    apply_surface(POSITION, POSITION, message, screen, NULL);
    apply_surface(POSITION, POSITION + 50, number, screen, NULL);
    SDL_Flip(screen);
    c_down.start();

    while (1) {
        if (c_down.get_ticks() >= 1000) {
            if (c_down.get_ticks() >= 2000 && c_down.get_ticks() <= 2100) {
                number = TTF_RenderText_Solid(font, "1", txtcolor);
                fill_white();
                apply_surface(POSITION, POSITION, message, screen, NULL);
                apply_surface(POSITION, POSITION + 50, number, screen, NULL);
                SDL_Flip(screen);
                continue;

            } else if (c_down.get_ticks() >= 2000)
                break;

            else if (c_down.get_ticks() <= 1100) {
                number = TTF_RenderText_Solid(font, "1", txtcolor);
                fill_white();
                apply_surface(POSITION, POSITION, message, screen, NULL);
                apply_surface(POSITION, POSITION + 50, number, screen, NULL);
                SDL_Flip(screen);
            }
        }
    }

}

void Stage::create_random_golis() {
    int i;

    for (i = 0; i < no_of_bullets; i++) {
        if (bullet[i].exist == false) {

            if (rand() % 2)
                bullet[i].gol = new Goli(SCREEN_WIDTH - 11, SCREEN_HEIGHT - height[rand() % 7],
                                         9, "ball.png", -speed[rand() % 5], 0, 0);
            else
                bullet[i].gol = new Goli(10, SCREEN_HEIGHT - height[rand() % 7], 9, "ball.png", speed[rand() % 5], 0,
                                         0);

            bullet[i].exist = true;
        }
    }
}

bool Stage::check_random_collision() {
    int i;
    for (i = 0; i < no_of_bullets; i++) {
        if (bullet[i].exist == true) {
            if (bullet[i].gol->check_for_collision()) {
                if (total > score)
                    score_write(total);
                return true;
            }
        }
    }
    return false;
}

void Stage::render_random_golis() {
    int i, j = 0;
    stringstream count;

    for (i = 0; i < no_of_bullets; i++) {
        j++;
        if (bullet[i].exist == true) {
            if (!(bullet[i].gol->update())) {
                delete bullet[i].gol;
                bullet[i].gol = NULL;
                bullet[i].exist = false;
                Mix_PlayChannel(0, bullet_sound, 0);
                total++;

            }
        }
    }
    //itoa(Stage::total, number, 10);
    ::sprintf(number, "%ld", Stage::total);
    Game::message = TTF_RenderText_Solid(Game::font, number, txtcolor);

    //itoa(score, number, 10);
    ::sprintf(number, "%ld", score);
    count << "highscore: " << number;

    Game::message1 = TTF_RenderText_Solid(font, count.str().c_str(), txtcolor);

    Game::fill_top();
    Game::apply_surface(10, 30, Game::message, Game::screen, NULL);
    Game::apply_surface(600, 30, Game::message1, Game::screen, NULL);
    SDL_Flip(Game::screen);
}
