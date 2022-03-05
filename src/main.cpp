#include <iostream>
#include <array>
#include <cmath>
#include <cstdlib>
#include <map>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "mutantris.hpp"
#include "current_piece.hpp"
// #include "purplege.hpp"
// otgamefw
// mutantris
const float BLOCK_WIDTH = 32.f;
const float BLOCK_HEIGHT = 32.f;

const int PANEL_WIDTH = 10;
const int PANEL_HEIGHT = 18;

const float PANEL_X = 64.f;
const float PANEL_Y = 8.f;
const float TOTAL_WIDTH = PANEL_WIDTH*BLOCK_WIDTH;
const float TOTAL_HEIGHT = PANEL_HEIGHT*BLOCK_HEIGHT;

int int1to(const int max) {
    return 1 + rand()%max;
}

struct Position {
    int x, y;

    Position() : x(0), y(0) {}

};

void draw_panel_background() {
    static const ALLEGRO_COLOR BLACK = al_map_rgba(0, 0, 0, 255);
    al_draw_rectangle(PANEL_X, PANEL_Y, PANEL_X+TOTAL_WIDTH, PANEL_Y+TOTAL_HEIGHT, BLACK, 1.f);
}

void reset_timer(ALLEGRO_TIMER *timer) {
    al_stop_timer(timer);
    al_start_timer(timer);
}

void draw_grid() {
    static const ALLEGRO_COLOR BLACK = al_map_rgba(0, 0, 0, 255);
    static const ALLEGRO_COLOR LIGHT_GREY = al_map_rgba(200, 200, 200, 255);
    //draw horizontal lines
    for (float y = 1.f; y < PANEL_HEIGHT; y += 1.f) {
        al_draw_line(PANEL_X, PANEL_Y+y*BLOCK_HEIGHT,
                     PANEL_X+TOTAL_WIDTH, PANEL_Y+y*BLOCK_HEIGHT,
                     LIGHT_GREY, 1.f);
    }
    //draw vertical lines
    for(float x = 1.f; x < PANEL_WIDTH; x += 1.f) {
        al_draw_line(PANEL_X+x*BLOCK_WIDTH, PANEL_Y,
                     PANEL_X+x*BLOCK_WIDTH, PANEL_Y+TOTAL_HEIGHT,
                     LIGHT_GREY, 1.f);

    }
}

void draw_panel(mutantris::Panel &panel, std::map<int, ALLEGRO_COLOR> color) {
    static const ALLEGRO_COLOR RED = al_map_rgba(255, 0, 0, 255);
    auto content = panel.getContent();
    //draw grid
    // draw blocks
    for (int y = 0; y < PANEL_HEIGHT; y++) {
        for (int x = 0; x < PANEL_WIDTH; x++) {
            if (content[y][x] == 0) {
                continue;
            }
            al_draw_filled_rectangle(PANEL_X+x*BLOCK_WIDTH, PANEL_Y+y*BLOCK_HEIGHT,
                                     PANEL_X+x*BLOCK_WIDTH+BLOCK_WIDTH, PANEL_Y+y*BLOCK_HEIGHT+BLOCK_HEIGHT,
                                     color[content[y][x]]);
        }
    }
}

void player_input(ALLEGRO_EVENT &event, mutantris::Panel &panel,
                  mutantris::Panel &background_panel, Position &position, CurrentPiece &current_piece, ALLEGRO_TIMER *game_timer) {
    static const int angle = 90*M_PI/180;
    switch(event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_A:
                    if (panel.move(-1, 0, background_panel)) {
                        position.x += -1;
                    }
                    break;
                case ALLEGRO_KEY_D:
                    if (panel.move(1, 0, background_panel)) {
                        position.x += 1;
                    }
                    break;
                case ALLEGRO_KEY_S:
                    while(panel.move(0, 1, background_panel) == true){
                        position.y++;
                    }
                    reset_timer(game_timer);
                    std::cout << "Clack!" << std::endl;
                    break;
                case ALLEGRO_KEY_SPACE:
                    auto done = panel.rotate(angle, position.x-1, position.y-1);
                    std::cout << "rotated: " << done << std::endl;
                    break;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_R) {
                mutantris::Piece piece_next = current_piece.next();
                panel.setPiece(position.x, position.y, piece_next, background_panel, int1to(6));
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                std::cout << "mouse button down" << std::endl;
                if (event.mouse.button == 1) {
                    mutantris::Piece piece_next = current_piece.next();
                    panel.setPiece(position.x, position.y, piece_next, background_panel, int1to(6));
                    std::cout << "1" << std::endl;
                }
                else if (event.mouse.button == 2) {
                    mutantris::Piece piece_before = current_piece.before();
                    panel.setPiece(position.x, position.y, piece_before, background_panel, int1to(6));
                    std::cout << "2" << std::endl;
                }
            break;
    }

}

int main(int argn, char* argv[]) {
    std::cout << "Starting this" << std::endl;
    al_init();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_joystick();
    //al_install_haptic();
    ALLEGRO_DISPLAY *display = al_create_display(800, 600);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_TIMER *panel_tick = al_create_timer(1.);
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_joystick_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(panel_tick));
    ALLEGRO_EVENT event;
    ALLEGRO_COLOR bgcolor = al_map_rgba(245, 245, 245, 0);
    std::map<int, ALLEGRO_COLOR> color {
        {1, al_map_rgba(240, 128, 128, 255)},
        {2, al_map_rgba(144, 238, 144, 255)},
        {3, al_map_rgba(100, 149, 237, 255)},
        {4, al_map_rgba(175, 238, 238, 255)},
        {5, al_map_rgba(221, 160, 221, 255)},
        {6, al_map_rgba(240, 230, 140, 255)},
    };
    bool running = true;
    mutantris::Panel panel(PANEL_WIDTH, PANEL_HEIGHT);
    mutantris::Panel playerPanel(PANEL_WIDTH, PANEL_HEIGHT);
    Position piecePosition;
    piecePosition.x = 4;
    piecePosition.y = 4;
    CurrentPiece current_piece;
    std::cout << "set piece: "
    << playerPanel.setPiece(piecePosition.x, piecePosition.y,
                            current_piece.randomize(), playerPanel, int1to(6)) << std::endl;
    al_start_timer(panel_tick);
    while (running) {
        if (al_get_next_event(queue, &event) == true) {
            switch (event.type) {
                case ALLEGRO_EVENT_KEY_DOWN:
                    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                        running = false;
                    }
                    break;
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    running = false;
                    break;
                case ALLEGRO_EVENT_TIMER:
                    if (event.timer.source == panel_tick) {
                        if (playerPanel.move(0, 1, panel) == false ) {
                            panel.addFrom(playerPanel);
                            playerPanel.clear();
                            piecePosition.x = 4;
                            piecePosition.y = 4;
                            auto lines = panel.checkLines();
                            auto [ start_line, end_line ] = lines;
                            std::cout << start_line << ", " << end_line << std::endl;
                            if (start_line != 0 and end_line != 0) {
                                panel.clearLines(lines);
                            }
                            playerPanel.setPiece(piecePosition.x, piecePosition.y, current_piece.randomize(), playerPanel, int1to(6));
                            std::cout << "clack! Next piece!" << std::endl;
                        } else {
                            piecePosition.y += 1;
                        }
                    }
            }
            player_input(event, playerPanel, panel, piecePosition, current_piece, panel_tick);
        }
        al_clear_to_color(bgcolor);
        draw_panel_background();
        draw_panel(panel, color);
        draw_panel(playerPanel, color);
        draw_grid();
        al_flip_display();
    }
    al_destroy_timer(panel_tick);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    std::cout << "Bye!" << std::endl;
    return 0;
}
