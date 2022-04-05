#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <allegro5/allegro.h>

/**
 * This is reverse timer, or countdown
 */
class Timer {
    int sec;
    int min;
    ALLEGRO_TIMER *timer;

    public:
        Timer();
        ~Timer();

        void set(int, int);
        void tick();
        const char *string(char[], int);
        bool finished();
        void stop();
        void start();
        void resume();
        ALLEGRO_TIMER *get_timer();
};

#endif
