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

#ifndef _MUTANTRIS_H_
#define _MUTANTRIS_H_

#include <array>
#include <vector>
#include <tuple>

namespace mutantris {
    /**
     * 0 -> Empty
     * n > 0 -> Not empty, numbers can be used for colors
     */
    const int PIECE_SIZE = 4;

    using Column = std::array<int, PIECE_SIZE>;
    using Piece = std::array<Column, PIECE_SIZE>;
    using Matrix = std::vector<std::vector<int>>;
    using Lines = std::array<int, 4>;

    constexpr Piece I = {
        Column{0, 1},
        Column{0, 1},
        Column{0, 1},
        Column{0, 1},
    };

    constexpr Piece O = {
        Column{1, 1},
        Column{1, 1},
    };

    constexpr Piece T = {
        Column{1, 1, 1},
        Column{0, 1, 0},
    };

    constexpr Piece L = {
        Column{0, 1, 0},
        Column{0, 1, 0},
        Column{0, 1, 1},
    };

    constexpr Piece IL = {
        Column{0, 1},
        Column{0, 1},
        Column{1, 1},
    };

    constexpr Piece Z = {
        Column{1, 1, 0},
        Column{0, 1, 1},
    };

    constexpr Piece S = {
        Column{0, 1, 1},
        Column{1, 1, 0},
    };

    class Panel {
        int width, height;
        Matrix content;
        Matrix next;
        Lines lines;

        void clearMatrix(Matrix &matrix);
        void copyNextToContent();

    public:
        Panel(const int width, const int height);

        Matrix& getContent();
        bool move(int x, int y, const mutantris::Panel &);
        bool setPiece(int x, int y, const Piece& piece, const Panel &, const int);
        bool rotate(float angle, int point_x, int point_y);
        bool addFrom(mutantris::Panel &);
        void clear();
        std::tuple<Lines, int> checkLines();
        bool clearLines();
    };

}

#endif
