#include <iostream>
#include <cstdio>
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
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    event_queue = al_create_event_queue();
    current_speed = DEFAULT_SPEED;
    panel_tick = al_create_timer(current_speed);
    general_font = al_load_ttf_font("assets/RedHatMono-VariableFont_wght.ttf", 32, 0);
    title_font = al_load_ttf_font("assets/RedHatMono-VariableFont_wght.ttf", 64, 0);
    small_font = al_load_ttf_font("assets/RedHatMono-VariableFont_wght.ttf", 16, 0);
    points = 0;
    period_of_grace = 0.;
    abuse_negation.set_capacity(5);
    status = Status::MAIN_SCREEN;
    timer.set(2, 0);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_joystick_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(panel_tick));
    al_register_event_source(event_queue, al_get_timer_event_source(timer.get_timer()));

}

Game::~Game() {
    std::cout << "Destruction!" << std::endl;

    al_destroy_timer(panel_tick);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_font(general_font);
    al_destroy_font(title_font);
    al_destroy_font(small_font);
}

void Game::run() {
    const auto MAX_TIMER_STR = 8;
    const auto MAX_POINTS_STR = 16;
    const auto POINTS_STR_POS_X = 64.f+TOTAL_WIDTH+8.f;
    ALLEGRO_COLOR bgcolor = al_map_rgba(245, 245, 245, 0);
    ALLEGRO_COLOR black = al_map_rgba(0, 0, 0, 255);
    bool running = true;
    mutantris::Panel game_panel(PANEL_WIDTH, PANEL_HEIGHT);
    mutantris::Panel player_panel(PANEL_WIDTH, PANEL_HEIGHT);
    PanelDrawer panel_drawer(64.f, 8.f, 10, 18, 32.f,
                             al_map_rgba(0, 0, 0, 128),
                             al_map_rgba(255, 255, 255, 255),
                             al_map_rgba(128, 128, 128, 255));

    mutantris::Panel next_piece_panel(4, 4);
    PanelDrawer next_piece_drawer(POINTS_STR_POS_X, 8.f+128.f+16.f, 4, 4, 32.f,
                                al_map_rgba(0, 0, 0, 128),
                                al_map_rgba(255, 255, 255, 255),
                                al_map_rgba(128, 128, 128, 255));

    char points_str[MAX_POINTS_STR] = {0};
    char timer_str[MAX_TIMER_STR] = {0};

    while (running == true) {
        input(running);
        process(game_panel, player_panel, next_piece_panel);

        al_clear_to_color(bgcolor);

        if (status == Status::MAIN_SCREEN) {
            drawMainScreen();
            al_flip_display();
            al_rest(0.1);
            continue;
        }

        // draw running and paused game
        panel_drawer.draw(game_panel.getContent(), player_panel.getContent());
        al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f, 0, "POINTS");

        snprintf(points_str, MAX_POINTS_STR, "%d", points);
        al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f+32.f+8.f, 0, static_cast<const char *>(points_str));

        if (status == Status::RUNNING) {
            al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f+64.f+24.f, 0, "NEXT");
            next_piece_drawer.draw_single(next_piece_panel.getContent());
        } else if (status == Status::PAUSE){
            al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f+64.f+24.f, 0, "PAUSE");
        } else if (status == Status::GAME_OVER) {
            al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f+64.f+24.f, 0, "GAME OVER!!");
            al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f+64.f+32.f+24.f, 0, "Press 'Enter'");
        }

        al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f+256.f+24.f, 0, "TIME");
        al_draw_text(general_font, black, POINTS_STR_POS_X, 8.f+256.f+32.f+24.f, 0,
                     timer.string(timer_str, MAX_TIMER_STR));

        al_flip_display();
    }
}

void Game::start() {
    current_speed = DEFAULT_SPEED;
    al_set_timer_speed(panel_tick, current_speed);
    status = Status::RUNNING;
    timer.stop();
    timer.set(2, 0);
    timer.start();
    points = 0;
    abuse_negation.clear();
    current_piece.randomize();
    reset_timer(panel_tick);
    event_manager.addEvent(Event::Type::START_GAME);
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
                case ALLEGRO_KEY_ENTER:
                    if (status == Status::RUNNING) {
                        status = Status::PAUSE;
                        timer.stop();
                    } else if (status == Status::PAUSE) {
                        status = Status::RUNNING;
                        timer.resume();
                    } else if (status == Status::MAIN_SCREEN) {
                        start();
                    } else if (status == Status::GAME_OVER) {
                        status = Status::MAIN_SCREEN;
                    }
                }
            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
        }
        if (status == Status::RUNNING) {
            running_input(event);
        }
    }
}

void Game::running_input(ALLEGRO_EVENT &event) {
    switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            switch(event.keyboard.keycode) {
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
        case ALLEGRO_EVENT_TIMER:
            if (event.timer.source == panel_tick) {
                event_manager.addEvent(Event::Type::GAME_TICK);
            }
            else if (event.timer.source == timer.get_timer()) {
                timer.tick();
                if (timer.finished()) {
                    event_manager.addEvent(Event::Type::GAME_OVER);
                }
            }
            break;
    }
}

void Game::process(mutantris::Panel &game_panel, mutantris::Panel &player_panel,
                   mutantris::Panel &next_piece_panel) {
    static const int angle = 90*M_PI/180;
    Event game_event;
    while(event_manager.nextEvent(game_event)) {
        std::cout << "game event type: " << game_event.type << std::endl;
        switch(game_event.type) {
            case Event::Type::START_GAME:
                game_panel.clear();
                addNextPiece(player_panel, next_piece_panel);
                break;
            case Event::Type::GAME_TICK:
            if (period_of_grace > 0.) {
                period_of_grace -= current_speed;
                break;
            }
            if (player_panel.move(0, 1, game_panel) == false ) {
                event_manager.addEvent(Event::Type::PIECE_DROPPED);
            } else {
                piece_position.y += 1;
            }
            break;
            case Event::Type::PIECE_DROPPED:
                game_panel.addFrom(player_panel);
                player_panel.clear();
                points++;
                {
                    const auto [ lines, completed_lines ] = game_panel.checkLines();
                    if (completed_lines > 0) {
                        event_manager.addLinesEvent(lines, completed_lines);
                    }
                    abuse_negation.push_value(current_piece.getIndex());
                    addNextPiece(player_panel, next_piece_panel);
                }
                if (player_panel.move(0, 0, game_panel) == false) {
                    event_manager.addEvent(Event::Type::GAME_OVER);
                }
                break;
            case Event::Type::CLEAR_LINES:
            {
                const auto total_lines = game_event.lines.cleared;
                std::cerr << "lines cleared: " << total_lines << std::endl;
                const auto temp_points = total_lines*total_lines;
                points += abuse_negation.punish(temp_points, current_piece.getIndex());
            }
                game_panel.clearLines();
                break;
            case Event::Type::PIECE_MOVES:
                if (period_of_grace > 0.) {
                    break;
                }
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
                current_piece.next();
                auto piece = current_piece.getCurrentPiece();
                player_panel.setPiece(piece_position.x, piece_position.y, piece, game_panel, int1to(6));
                period_of_grace = PERIOD_OF_GRACE;
            }
                break;
            case Event::Type::PIECE_NEXT_MUTATION:
            {
                current_piece.next();
                auto piece = current_piece.getCurrentPiece();
                player_panel.setPiece(piece_position.x, piece_position.y, piece, game_panel, int1to(6));
                period_of_grace = PERIOD_OF_GRACE;
            }
                break;
            case Event::Type::PIECE_LAST_MUTATION:
            {
                current_piece.before();
                auto piece = current_piece.getCurrentPiece();
                player_panel.setPiece(piece_position.x, piece_position.y, piece, game_panel, int1to(6));
                period_of_grace = PERIOD_OF_GRACE;
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
            case Event::Type::GAME_OVER:
                status = Status::GAME_OVER;
                timer.stop();
                al_stop_timer(panel_tick);
                break;
        }
    }
}

void Game::addNextPiece(mutantris::Panel &player_panel, mutantris::Panel &next_piece_panel) {
    auto piece = CurrentPiece::PIECES[next_piece.index];
    piece_position.x = PANEL_WIDTH / 2;
    piece_position.y = 2;
    const auto value = next_piece.value > 0 ? next_piece.value : int1to(6);
    player_panel.setPiece(piece_position.x, piece_position.y, piece, player_panel, value);

    next_piece.index = current_piece.randomize();
    next_piece.value = int1to(6);
    next_piece_panel.setPiece(2, 2, current_piece.getCurrentPiece(), next_piece_panel, next_piece.value);
}

void Game::drawMainScreen() {
    static ALLEGRO_COLOR black = al_map_rgba(0, 0, 0, 255);
    static const char *TITLE = "PASTMUTANTRIS";
    static const char *AUTHOR = "Oscar Triano García @cat_dotoscat 2022";
    static const char *HOW_TO_START = "Press 'Enter' to start.";

    static const int title_width = al_get_text_width(title_font, TITLE);
    static const float title_x = (SCREEN_WIDTH - title_width) / 2.f;
    static const int start_width = al_get_text_width(general_font, HOW_TO_START);
    static const float start_x = (SCREEN_WIDTH - start_width) / 2.f;

    al_draw_text(title_font, black, title_x, 8.f, 0, TITLE);
    al_draw_text(general_font, black, start_x, SCREEN_HEIGHT/2, 0, HOW_TO_START);
    al_draw_text(small_font, black, 8.f, SCREEN_HEIGHT-32.f, 0, AUTHOR);
}
