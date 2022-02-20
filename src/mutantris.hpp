#ifndef _MUTANTRIS_H_
#define _MUTANTRIS_H_

#include <array>
#include <vector>

namespace mutantris {
    /**
     * 0 -> Empty
     * n > 0 -> Not empty, numbers can be used for colors
     */
    const int PIEZE_SIZE = 4;

    using Column = std::array<int, PIEZE_SIZE>;
    using Piece = std::array<Column, PIEZE_SIZE>;
    using Matrix = std::vector<std::vector<int>>;

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

        void clearMatrix(Matrix &matrix);
        void copyNextToContent();

    public:
        Panel(const int width, const int height);

        Matrix& getContent();
        bool move(int x, int y);
        bool setPiece(int x, int y, const Piece& piece);
        bool rotate(float angle, int point_x, int point_y);
    };

}

#endif
