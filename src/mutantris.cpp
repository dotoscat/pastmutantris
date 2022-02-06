#include "mutantris.hpp"

mutantris::Panel::Panel(const int width, const int height) {
    for(int y = 0; y < height; y++) {
        mutantris::Column column(width, 0);
        content.push_back(column);
    }
}

std::vector<mutantris::Column>& mutantris::Panel::getContent() {
    return content;
}
