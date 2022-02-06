#include <iostream>
#include "purplege.hpp"

purplege::Purplege::Purplege() {
    display = al_create_display(0, 0);
}

purplege::Purplege::~Purplege() {
    std::cout << "Destroy purplege" << std::endl;
    al_destroy_display(display);
}

int purplege::run() {
    return 0;
}
