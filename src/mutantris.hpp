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
        std::vector<Column> content;
    public:
        Panel(const int width, const int height);

        std::vector<Column>& getContent();
    };

}

#endif
