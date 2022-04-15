// Copyright 2022 Oscar Triano García
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

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
