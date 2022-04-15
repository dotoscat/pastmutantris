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

#include "event_manager.hpp"

EventManager::EventManager() : used(0) {
    events.reserve(MAX_EVENTS);
}

constexpr bool EventManager::empty() {
    return used == 0;
}

bool EventManager::nextEvent(Event &event){
    if (empty()) {
        return false;
    }
    event = events[used];
    used--;
    return true;
}

void EventManager::addEvent(Event::Type type) {
    if (used == MAX_EVENTS) {
        return;
    }
    used++;
    events[used].type = type;
}

void EventManager::addPieceEvent(Event::Type type, int index_piece) {
    if (used == MAX_EVENTS) {
        return;
    }
    used++;
    events[used].type = type;
    events[used].index_piece = index_piece;
}

void EventManager::addLinesEvent(mutantris::Lines lines, int lines_cleared) {
    if (used == MAX_EVENTS) {
        return;
    }
    used++;
    events[used].type = Event::Type::CLEAR_LINES;
    events[used].lines.lines = lines;
    events[used].lines.cleared = lines_cleared;
}

void EventManager::addMoveEvent(Event::Move move) {
    if (used == MAX_EVENTS) {
        return;
    }
    used++;
    events[used].type = Event::Type::PIECE_MOVES;
    events[used].move = move;
}
