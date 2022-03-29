#include <iostream>
#include <array>
#include <vector>
#include <map>
#include "game.hpp"
#include "mutantris.hpp"
#include "current_piece.hpp"
#include "panel_drawer.hpp"

int int1to(const int max) {
    return 1 + rand()%max;
}


void reset_timer(ALLEGRO_TIMER *timer) {
    al_stop_timer(timer);
    al_start_timer(timer);
}

Game::Game() {
    display = al_create_display(800, 600);
    event_queue = al_create_event_queue();
    current_speed = DEFAULT_SPEED;
    panel_tick = al_create_timer(current_speed);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_joystick_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(panel_tick));

}

Game::~Game() {
    std::cout << "Destruction!" << std::endl;

    al_destroy_timer(panel_tick);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
}

void Game::run() {
    ALLEGRO_COLOR bgcolor = al_map_rgba(245, 245, 245, 0);
    bool running = true;
    mutantris::Panel game_panel(PANEL_WIDTH, PANEL_HEIGHT);
    mutantris::Panel player_panel(PANEL_WIDTH, PANEL_HEIGHT);
    PanelDrawer panel_drawer(64.f, 8.f, 10, 18, 32.f,
                             al_map_rgba(0, 0, 0, 128),
                             al_map_rgba(255, 255, 255, 255),
                             al_map_rgba(128, 128, 128, 255));
    piece_position.x = 4;
    piece_position.y = 4;

    std::cout << player_panel.setPiece(piece_position.x, piece_position.y,
                            current_piece.randomize(), player_panel, int1to(6)) << std::endl;
    al_start_timer(panel_tick);
    while (running == true) {
        input(running);
        process(game_panel, player_panel);
        al_clear_to_color(bgcolor);
        panel_drawer.draw(game_panel.getContent(), player_panel.getContent());
        al_flip_display();

    }
}

void Game::input(bool &running) {
    ALLEGRO_EVENT event;
    while(al_get_next_event(event_queue, &event) == true) {
        switch (event.type) {
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    running = false;
                    break;
                case ALLEGRO_KEY_A:
                    event_manager.addMoveEvent(Event::Move::LEFT);
                    break;
                case ALLEGRO_KEY_D:
                    event_manager.addMoveEvent(Event::Move::RIGHT);
                    break;
                case ALLEGRO_KEY_S:
                    event_manager.addEvent(Event::Type::PIECE_FAST_FALL);
                    break;
                case ALLEGRO_KEY_SPACE:
                    event_manager.addEvent(Event::Type::PIECE_ROTATES);
                    break;
                case ALLEGRO_KEY_R:
                    event_manager.addEvent(Event::Type::PIECE_MUTATES);
                    break;
                }
            case ALLEGRO_EVENT_KEY_UP:
                switch(event.keyboard.keycode) {
                    case ALLEGRO_KEY_S:
                        event_manager.addEvent(Event::Type::PIECE_NORMAL_FALL);
                        break;
                }
            break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (event.mouse.button == 1) {
                    event_manager.addEvent(Event::Type::PIECE_NEXT_MUTATION);
                    std::cout << "1" << std::endl;
                }
                else if (event.mouse.button == 2) {
                    event_manager.addEvent(Event::Type::PIECE_LAST_MUTATION);
                    std::cout << "2" << std::endl;
                }
            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                if (event.timer.source == panel_tick) {
                    event_manager.addEvent(Event::Type::GAME_TICK);
                }
                break;
        }

    }
}

void Game::process(mutantris::Panel &game_panel, mutantris::Panel &player_panel) {
    static const int angle = 90*M_PI/180;
    Event game_event;
    while(event_manager.nextEvent(game_event)) {
        std::cout << "game event type: " << game_event.type << std::endl;
        switch(game_event.type) {
            case Event::Type::GAME_TICK:
            if (player_panel.move(0, 1, game_panel) == false ) {
                event_manager.addEvent(Event::Type::PIECE_DROPPED);
            } else {
                piece_position.y += 1;
            }
            break;
            case Event::Type::PIECE_DROPPED:
                game_panel.addFrom(player_panel);
                player_panel.clear();
                piece_position.x = 4;
                piece_position.y = 4;
                {
                    const auto [ lines, there_are_lines ] = game_panel.checkLines();
                    if (there_are_lines) {
                        event_manager.addLinesEvent(lines);
                    }
                }
                player_panel.setPiece(piece_position.x, piece_position.y, current_piece.randomize(), player_panel, int1to(6));
                break;
            case Event::Type::CLEAR_LINES:
                game_panel.clearLines(game_event.lines.start, game_event.lines.end);
                break;
            case Event::Type::PIECE_MOVES:
            {
                const auto direction =
                    game_event.move == Event::Move::LEFT ? -1 :
                    game_event.move == Event::Move::RIGHT ? 1 : 0;
                if (player_panel.move(direction, 0, game_panel)) {
                    piece_position.x += direction;
                }
            }
            break;
            case Event::Type::PIECE_ROTATES:
            {
                auto done = player_panel.rotate(angle, piece_position.x-1, piece_position.y-1);
                std::cerr << "Piece rotates: " << done << std::endl;
            }
            break;
            case Event::Type::PIECE_MUTATES:
            {
                mutantris::Piece piece_next = current_piece.next();
                player_panel.setPiece(piece_position.x, piece_position.y, piece_next, game_panel, int1to(6));
            }
                break;
            case Event::Type::PIECE_NEXT_MUTATION:
            {
                mutantris::Piece piece_next = current_piece.next();
                player_panel.setPiece(piece_position.x, piece_position.y, piece_next, game_panel, int1to(6));
            }
                break;
            case Event::Type::PIECE_LAST_MUTATION:
            {
                mutantris::Piece piece_before = current_piece.before();
                player_panel.setPiece(piece_position.x, piece_position.y, piece_before, game_panel, int1to(6));
            }
                break;
            case Event::Type::PIECE_FAST_FALL:
                al_set_timer_speed(panel_tick, current_speed/16.);
                reset_timer(panel_tick);
                break;
            case Event::Type::PIECE_NORMAL_FALL:
                al_set_timer_speed(panel_tick, current_speed);
                reset_timer(panel_tick);
                break;
        }
    }
}
