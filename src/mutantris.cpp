#include "mutantris.hpp"

void mutantris::Panel::clearNext() {
    for (auto &row : next) {
        for(auto &c : row) {
            c = 0;
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
    for (int py = 0; py < height; py++) {
        for(int px = 0; px < width; px++) {
            content[py][px] = next[py][px];
        }
    }
    clearNext();
    return true;
}

bool mutantris::Panel::setPiece(int x, int y, Piece& piece) {
    if (x < 0 || x >= width || y < 0 || y >= height ||
        x+mutantris::PIEZE_SIZE < 0 || x+mutantris::PIEZE_SIZE >= width ||
        y+mutantris::PIEZE_SIZE < 0 || y+mutantris::PIEZE_SIZE >= height
    ) {
        return false;
    }
    //Copy
    for (int iy = 0; iy < mutantris::PIEZE_SIZE; iy++) {
        for (int ix = 0; ix < mutantris::PIEZE_SIZE; ix++) {
            content[y+iy][x+ix] = piece[iy][ix];
        }
    }
    return true;
}
