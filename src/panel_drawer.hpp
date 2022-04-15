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

#ifndef _PANEL_DRAWER_
#define _PANEL_DRAWER_

#include <map>
#include <allegro5/allegro.h>
#include "mutantris.hpp"

class PanelDrawer {

    static inline std::map<int, ALLEGRO_COLOR> COLORS;

    const float X, Y, WIDTH, HEIGHT, BLOCK_SIZE;
    const int BLOCK_WIDTH, BLOCK_HEIGHT;
    ALLEGRO_COLOR bg_color;
    ALLEGRO_COLOR bg_lines_color;
    ALLEGRO_COLOR grid_color;

    static void init_colors();
    void draw_matrix(mutantris::Matrix &);
    void draw_lines();

    public:
        PanelDrawer(float, float, int, int, float,
                    ALLEGRO_COLOR, ALLEGRO_COLOR, ALLEGRO_COLOR);
        void draw(mutantris::Matrix &, mutantris::Matrix &);
        void draw_single(mutantris::Matrix &);

};

#endif
