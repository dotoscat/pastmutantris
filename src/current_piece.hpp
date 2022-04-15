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

#ifndef _CURRENT_PIECE_HPP_
#define _CURRENT_PIECE_HPP_

#include <array>
#include "mutantris.hpp"

class CurrentPiece {
    static constexpr auto TOTAL_PIECES = 7;
    int current_piece;

public:
    static constexpr std::array<mutantris::Piece, TOTAL_PIECES> PIECES = {
        mutantris::I,
        mutantris::O,
        mutantris::T,
        mutantris::L,
        mutantris::IL,
        mutantris::S,
        mutantris::Z,
    };


public:
    CurrentPiece() : current_piece(0) {};

    int getIndex();
    bool setIndex(int);
    mutantris::Piece getCurrentPiece();
    int next();
    int before();
    int randomize();

};

#endif
