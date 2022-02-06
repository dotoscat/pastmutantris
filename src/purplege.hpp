# ifndef _PURPLEGE_HPP_
# define _PURPLEGE_HPP_

#include <allegro5/allegro.h>

namespace purplege {

    class Purplege {
        ALLEGRO_DISPLAY *display;
        ALLEGRO_COLOR bgColor;
    public:
        Purplege();
        ~Purplege();


    };

    int run();
}

#endif
