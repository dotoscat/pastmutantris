#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <cstdlib>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "event_manager.hpp"
#include "current_piece.hpp"

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

class Game {

    static constexpr double DEFAULT_SPEED = 1.;
    double current_speed;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *panel_tick;
    ALLEGRO_FONT *general_font;
    EventManager event_manager;
    Position piece_position;
    CurrentPiece current_piece;
    int points;

    void input(bool &);
    void process(mutantris::Panel &, mutantris::Panel &);
    void addNextPiece(mutantris::Panel &);

    public:
        Game();
        ~Game();

        void run();
};

#endif
