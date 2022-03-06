#include <allegro5/allegro_primitives.h>
#include "panel_drawer.hpp"

void PanelDrawer::init_colors() {
    if (PanelDrawer::COLORS.empty() == false) {
        return;
    }
    PanelDrawer::COLORS = {
        {1, al_map_rgba(240, 128, 128, 255)},
        {2, al_map_rgba(144, 238, 144, 255)},
        {3, al_map_rgba(100, 149, 237, 255)},
        {4, al_map_rgba(175, 238, 238, 255)},
        {5, al_map_rgba(221, 160, 221, 255)},
        {6, al_map_rgba(240, 230, 140, 255)},
    };
}

PanelDrawer::PanelDrawer(float x, float y, int block_width, int block_height, float block_size,
                         ALLEGRO_COLOR bg_color, ALLEGRO_COLOR bg_lines_color, ALLEGRO_COLOR grid_color):
X(x), Y(y), BLOCK_HEIGHT(block_height), BLOCK_WIDTH(block_width),
WIDTH(block_width*block_size), HEIGHT(block_height*block_size), BLOCK_SIZE(block_size),
bg_color(bg_color), bg_lines_color(bg_lines_color), grid_color(grid_color) {
        PanelDrawer::init_colors();
}

void PanelDrawer::draw_matrix(mutantris::Matrix &matrix) {
    // draw blocks
    for (int y = 0; y < BLOCK_HEIGHT; y++) {
        for (int x = 0; x < BLOCK_WIDTH; x++) {
            if (matrix[y][x] == 0) {
                continue;
            }
            al_draw_filled_rectangle(X+x*BLOCK_SIZE, Y+y*BLOCK_SIZE,
                                     X+x*BLOCK_SIZE+BLOCK_SIZE, Y+y*BLOCK_SIZE+BLOCK_SIZE,
                                     COLORS[matrix[y][x]]);
        }
    }
}

void PanelDrawer::draw(mutantris::Matrix &matrix, mutantris::Matrix &second_matrix) {
    // background color
    al_draw_filled_rectangle(X, Y, X+WIDTH, Y+HEIGHT, bg_color);

    draw_matrix(matrix);
    draw_matrix(second_matrix);

    //draw horizontal lines
    for (int y = 1; y < BLOCK_HEIGHT; y += 1) {
        al_draw_line(X, Y+y*BLOCK_SIZE,
                     X+WIDTH, Y+y*BLOCK_SIZE,
                     grid_color, 1.f);
    }
    //draw vertical lines
    for(int x = 1; x < BLOCK_WIDTH; x += 1) {
        al_draw_line(X+x*BLOCK_SIZE, Y,
                     X+x*BLOCK_SIZE, Y+HEIGHT,
                     grid_color, 1.f);
    }

}
