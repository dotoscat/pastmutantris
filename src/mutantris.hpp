#ifndef _MUTANTRIS_H_
#define _MUTANTRIS_H_

#include <vector>

namespace mutantris {
    /**
     * 0 -> Empty
     * n > 0 -> Not empty, numbers can be used for colors
     */
    const int PIEZE_SIZE = 4;

    using Column = std::vector<int>;
    using Piece = const int[PIEZE_SIZE][PIEZE_SIZE];

    Piece I = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
    };

    Piece O = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    Piece T = {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    };

    Piece L = {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    Piece IL = {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    Piece Z = {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    Piece S = {
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
    };

    class Panel {
        int width, height;
        std::vector<Column> content;
        std::vector<Column> next;

        void clearMatrix(std::vector<Column> &matrix);
        void copyNextToContent();

    public:
        Panel(const int width, const int height);

        std::vector<Column>& getContent();
        bool move(int x, int y);
        bool setPiece(int x, int y, Piece& piece);
        bool rotate(float angle, int point_x, int point_y);
    };

}

#endif
