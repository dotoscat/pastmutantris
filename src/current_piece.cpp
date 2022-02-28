#include <cstdlib>
#include "current_piece.hpp"

mutantris::Piece CurrentPiece::next() {
    current_piece++;
    if (current_piece >= TOTAL_PIECES) {
        current_piece = 0;
    }
    return PIECES[current_piece];
}

mutantris::Piece CurrentPiece::before() {
    current_piece--;
    if (current_piece < 0) {
        current_piece = TOTAL_PIECES-1;
    }
    return PIECES[current_piece];
}

mutantris::Piece CurrentPiece::randomize() {
    current_piece = rand()%TOTAL_PIECES;
    return PIECES[current_piece];
}
