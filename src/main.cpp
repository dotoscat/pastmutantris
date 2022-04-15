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
    al_set_app_name("pastmutantris");
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
    Game game;
    game.run();
}
