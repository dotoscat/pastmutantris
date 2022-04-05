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
