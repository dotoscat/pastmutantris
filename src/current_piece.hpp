#ifndef _CURRENT_PIECE_HPP_
#define _CURRENT_PIECE_HPP_

#include <array>
#include "mutantris.hpp"

class CurrentPiece {
    static constexpr auto TOTAL_PIECES = 7;
    static constexpr std::array<mutantris::Piece, TOTAL_PIECES> PIECES = {
        mutantris::I,
        mutantris::O,
        mutantris::T,
        mutantris::L,
        mutantris::IL,
        mutantris::S,
        mutantris::Z,
    };

    int current_piece;

public:
    CurrentPiece() : current_piece(0) {};

    int getIndex();
    mutantris::Piece getCurrentPiece();
    int next();
    int before();
    int randomize();

};

#endif
