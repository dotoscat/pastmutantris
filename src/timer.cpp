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

#include <cstdio>
#include "timer.hpp"

Timer::Timer(): sec(0), min(0), timer(al_create_timer(1.)) {}

Timer::~Timer() {
    al_destroy_timer(timer);
}

void Timer::set(int min, int sec) {
    this->min = min;
    this->sec = sec;
}

void Timer::tick() {
    sec -= 1;
    if (sec < 0) {
        sec = 59;
        min -= 1;
    }
}

const char *Timer::string(char buffer[], int size) {
    std::snprintf(buffer, size, "%02d:%02d", min, sec);
    return static_cast<const char *>(buffer);
}

bool Timer::finished(){
    return min <= 0 && sec <= 0;
}

void Timer::stop(){
    al_stop_timer(timer);
}

void Timer::start(){
    al_start_timer(timer);
}

void Timer::resume(){
    al_resume_timer(timer);
}

ALLEGRO_TIMER *Timer::get_timer() {
    return timer;
}
