#include <iostream>
#include "mutantris.hpp"

void mutantris::Panel::clearMatrix(std::vector<Column> &matrix) {
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
        mutantris::Column column(width, 0);
        content.push_back(column);
    }
    next = content;
    this->width = width;
    this->height = height;
}

std::vector<mutantris::Column>& mutantris::Panel::getContent() {
    return content;
}

/**
 * Return true if movement is made, false if not
 */
bool mutantris::Panel::move(int x, int y) {
    clearMatrix(next);
    for (int py = 0; py < height; py++) {
        for(int px = 0; px < width; px++) {
            if (content[py][px] == 0) {
                continue;
            }
            const int final_y = py + y;
            const int final_x = px + x;
            if (final_y < 0 || final_y >= height ||
                final_x < 0 || final_x >= width) {
                return false;
            }
            next[final_y][final_x] = content[py][px];
        }
    }
    copyNextToContent();
    return true;
}

bool mutantris::Panel::setPiece(int x, int y, Piece& piece) {
    if (x < 0  || y < 0
        || x+mutantris::PIEZE_SIZE > width
        || y+mutantris::PIEZE_SIZE > height
    ) {
        return false;
    }
    //Copy
    for (int iy = 0; iy < mutantris::PIEZE_SIZE; iy++) {
        for (int ix = 0; ix < mutantris::PIEZE_SIZE; ix++) {
            content[y+iy-PIEZE_SIZE/2][x+ix-PIEZE_SIZE/2] = piece[iy][ix];
        }
    }
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
