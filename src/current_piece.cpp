#include <cstdlib>
#include "current_piece.hpp"

int CurrentPiece::getIndex() {
    return current_piece;
}

bool CurrentPiece::setIndex(int index_piece) {
    if (index_piece < 0 || index_piece >= TOTAL_PIECES) {
        return false;
    }
    current_piece = index_piece;
    return true;
}

mutantris::Piece CurrentPiece::getCurrentPiece() {
    return PIECES[current_piece];
}

int CurrentPiece::next() {
    current_piece++;
    if (current_piece >= TOTAL_PIECES) {
        current_piece = 0;
    }
    return current_piece;
}

int CurrentPiece::before() {
    current_piece--;
    if (current_piece < 0) {
        current_piece = TOTAL_PIECES-1;
    }
    return current_piece;
}

int CurrentPiece::randomize() {
    current_piece = rand()%TOTAL_PIECES;
    return current_piece;
}
