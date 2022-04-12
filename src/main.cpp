#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "game.hpp"

int main(int argn, char* argv[]) {
    std::cout << "Starting this" << std::endl;
    al_init();
    al_install_audio();
    al_init_acodec_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_joystick();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_reserve_samples(4);
    // ALLEGRO_SAMPLE *sample = al_load_sample("assets/drop.wav");
    // bool valid = al_play_sample(sample, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, &id);
    // al_destroy_sample(sample);
    Game game;
    game.run();
}
