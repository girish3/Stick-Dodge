#ifndef ACTION_H

#define ACTION_H

#include "const.h"

using namespace std;
class action
{
    public:

        action(string img,int width,int height,int offset,int total);
        void apply_next_right();   //to apply the next surface
        void apply_next_left();   //to apply the next surface
        static void reset();
        virtual ~action();
    protected:
    private:
        SDL_Surface* image_seq;
        int width;
        int height;
        int offset; //where next image go
        static int next; // the next image to be applied
        int total; //total no. of images in the seq..
};


#endif // ACTION_H
