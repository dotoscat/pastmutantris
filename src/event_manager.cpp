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

void EventManager::addPieceEvent(Event::Type type, mutantris::Piece piece) {
    if (used == MAX_EVENTS) {
        return;
    }
    used++;
    events[used].type = type;
    events[used].piece = piece;
}

void EventManager::addLineEvent(int lines) {
    if (used == MAX_EVENTS) {
        return;
    }
    used++;
    events[used].type = Event::Type::CLEAR_LINE;
    events[used].lines = lines;
}

void EventManager::addMoveEvent(Event::Move move) {
    if (used == MAX_EVENTS) {
        return;
    }
    used++;
    events[used].type = Event::Type::PIECE_MOVES;
    events[used].move = move;
}
