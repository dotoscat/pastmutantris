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
#include "mutantris.hpp"

void mutantris::Panel::clearMatrix(Matrix &matrix) {
    for (auto &row : matrix) {
        for(auto &c : row) {
            c = 0;
        }
    }
}

void mutantris::Panel::copyNextToContent() {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            content[y][x] = next[y][x];
        }
    }
}

mutantris::Panel::Panel(const int width, const int height) {
    for(int y = 0; y < height; y++) {
        std::vector<int> column(width, 0);
        content.push_back(column);
    }
    next = content;
    this->width = width;
    this->height = height;
    lines = {0};
}

mutantris::Matrix& mutantris::Panel::getContent() {
    return content;
}

/**
 * Return true if movement is made, false if not
 */
bool mutantris::Panel::move(int x, int y, const mutantris::Panel &panel) {
    if (&panel != this && panel.width != width || panel.height != height) {
        return false;
    }
    clearMatrix(next);
    for (int py = 0; py < height; py++) {
        for(int px = 0; px < width; px++) {
            if (content[py][px] == 0) {
                continue;
            }
            const int final_y = py + y;
            const int final_x = px + x;
            if (final_y < 0 || final_y >= height ||
                final_x < 0 || final_x >= width || //check collision against panel content
                (&panel != this && panel.content[final_y][final_x] != 0)) {
                return false;
            }
            next[final_y][final_x] = content[py][px];
        }
    }
    copyNextToContent();
    return true;
}

bool mutantris::Panel::setPiece(int x, int y, const Piece& piece,
                                const mutantris::Panel &background_panel, int value) {
    clearMatrix(next);
    //Copy
    for (int iy = 0; iy < mutantris::PIECE_SIZE; iy++) {
        for (int ix = 0; ix < mutantris::PIECE_SIZE; ix++) {
            const int final_y = y+iy-PIECE_SIZE/2;
            const int final_x = x+ix-PIECE_SIZE/2;
            if (final_y < 0 || final_y >= height
                || final_x < 0 || final_x >= width
                || (&background_panel != this && background_panel.content[final_y][final_x] != 0)
            ) {
                return false;
            }
            next[final_y][final_x] = piece[iy][ix] == 0 ? 0 : value;
        }
    }
    copyNextToContent();
    return true;
}

bool mutantris::Panel::rotate(float angle, int point_x, int point_y){
    clearMatrix(next);
    for(int py = 0; py < height; py++){
        for(int px = 0; px < width; px++){
            if (content[py][px] == 0) {
                continue;
            }
            const int rotation_x = px - point_x;
            const int rotation_y = py - point_y;
            const int fx = -rotation_y + point_x;
            const int fy = rotation_x + point_y;
            if (fx < 0 || fx >= width || fy < 0 || fy >= height) {
                return false;
            }
            next[fy][fx] = content[py][px];
        }
    }
    copyNextToContent();
    return true;
}

bool mutantris::Panel::addFrom(mutantris::Panel &panel){
    if (panel.width != width || panel.height != height) {
        return false;
    }
    for (int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            auto panelContent = panel.getContent();
            if (panelContent[y][x] == 0){
                continue;
            }
            content[y][x] = panelContent[y][x];
        }
    }
    return true;
}

void mutantris::Panel::clear() {
    clearMatrix(content);
    clearMatrix(next);
}

std::tuple<mutantris::Lines, int> mutantris::Panel::checkLines() {
    int lines_i = 0;
    bool there_are_lines = false;
    for(int y = 0; y < height; y++) {
        bool completed = true;
        for (auto x : content[y]) {
           completed = completed && x != 0;
        }
        if (completed && lines_i < 4) {
            lines[lines_i] = y;
            lines_i++;
            there_are_lines = true;
        }
    }
    const auto number_of_lines = there_are_lines ? lines_i : 0;
    return std::make_tuple(lines, number_of_lines);
}

bool mutantris::Panel::clearLines() {
    bool done = false;
    for (int i = 0; i < 4; i++) {
        if (lines[i] <= 0) {
            continue;
        }
        const int i_line = lines[i];
        for(int y = i_line; y > 0; y--) {
            for(int x = 0; x < width; x++) {
                content[y][x] = content[y-1][x];
            }
        }
        lines[i] = 0;
        done = true;
    }
    return done;
}
