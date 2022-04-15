#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <array>
#include <map>
#include <cstdlib>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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

#include "event_manager.hpp"
#include "current_piece.hpp"
#include "abuse_negation.hpp"
#include "timer.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const float BLOCK_SIZE = 32.f;

const int PANEL_WIDTH = 10;
const int PANEL_HEIGHT = 18;

const float PANEL_X = 64.f;
const float PANEL_Y = 8.f;
const float TOTAL_WIDTH = PANEL_WIDTH*BLOCK_SIZE;
const float TOTAL_HEIGHT = PANEL_HEIGHT*BLOCK_SIZE;

struct Position {
    int x, y;

    Position() : x(0), y(0) {}

};

struct NextPiece {
    int index;
    int value;

    NextPiece() : index(0), value(0) {}
};

class Game {

    enum Status {
        MAIN_SCREEN,
       RUNNING,
       PAUSE,
       GAME_OVER
    } status;

    static constexpr auto MAX_POINTS_STR = 16;
    static constexpr double PERIOD_OF_GRACE = 1.;
    static constexpr double DEFAULT_SPEED = 1.;
    static constexpr double INCREASE_SPEED_MAX_TIME = 28.;
    double current_speed;
    double current_speed_increase_time;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *panel_tick;
    ALLEGRO_FONT *general_font;
    ALLEGRO_FONT *title_font;
    ALLEGRO_FONT *small_font;
    std::map<const char *, ALLEGRO_SAMPLE *> samples;
    EventManager event_manager;
    Position piece_position;
    CurrentPiece current_piece;
    NextPiece next_piece;
    double period_of_grace;
    AbuseNegation abuse_negation;
    Timer timer;

    int points;

    static constexpr size_t MAX_SCORE_LIST = 5;
    std::array<int, MAX_SCORE_LIST> score_list;

    void start();
    void input(bool &);
    void running_input(ALLEGRO_EVENT &);
    void process(mutantris::Panel &, mutantris::Panel &, mutantris::Panel &);
    void addNextPiece(mutantris::Panel &, mutantris::Panel &);
    void drawMainScreen();
    void playSample(const char *);
    ALLEGRO_FILE *openScoreList(const char *);
    void loadScoreList();
    void writeScoreList();
    void storeScoreInList();

    public:
        Game();
        ~Game();

        void run();
};

#endif
