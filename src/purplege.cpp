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
