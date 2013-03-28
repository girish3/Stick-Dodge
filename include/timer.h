#ifndef TIMER_H
#define TIMER_H


class timer
{
    public:
       timer();
       //following are all functions of class timer

       void start();
       void stop();
       void pause();
       void unpause();
       //Gets the timer's time
       int get_ticks();
       //Checks the status of the timer
       bool is_started();
       bool is_paused();

       virtual ~timer();

    private:
     int startTicks; //The ticks stored when the timer was paused
     int pausedTicks; //The timer status
     bool paused;
     bool started;
};

#endif // TIMER_H
