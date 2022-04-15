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
