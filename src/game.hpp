#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <map>
#include <cstdlib>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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

    void start();
    void input(bool &);
    void running_input(ALLEGRO_EVENT &);
    void process(mutantris::Panel &, mutantris::Panel &, mutantris::Panel &);
    void addNextPiece(mutantris::Panel &, mutantris::Panel &);
    void drawMainScreen();
    void playSample(const char *);

    public:
        Game();
        ~Game();

        void run();
};

#endif
