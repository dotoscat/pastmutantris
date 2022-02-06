#ifndef _MUTANTRIS_H_
#define _MUTANTRIS_H_

#include <vector>

namespace mutantris {
    /**
     * 0 -> Empty
     * n > 0 -> Not empty, numbers can be used for colors
     */
    using Column = std::vector<int>;

    class Panel {
        int width, height;
        std::vector<Column> content;
        std::vector<Column> next;
    public:
        Panel(const int width, const int height);

        std::vector<Column>& getContent();
        bool move(int x, int y);
    };

}

#endif
