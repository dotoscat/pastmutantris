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

#ifndef _EVENT_MANAGER_HPP_
#define _EVENT_MANAGER_HPP_

#include <vector>
#include "mutantris.hpp"

/**
 * Events
 *
 * Game Over
 * Piece moves -> what piece
 * Piece mutates -> what piece
 * Piece rotates -> what piece
 * Piece sets -> what piece?
 * clear 1 line
 * clear 2 lines
 * clear 3 lines
 * clear 4 lines
 *
 */
struct Event {
    enum Type{
        START_GAME,
        GAME_OVER,
        GAME_TICK,
        INCREASE_SPEED,
        PIECE_MOVES,
        PIECE_FAST_FALL,
        PIECE_NORMAL_FALL,
        PIECE_DROPPED,
        PIECE_ROTATES,
        PIECE_MUTATES,
        PIECE_NEXT_MUTATION,
        PIECE_LAST_MUTATION,
        CLEAR_LINES,
    } type;
    enum Move {
        LEFT,
        RIGHT,
        DROP
    };
    union {
        int index_piece;
        struct{
            mutantris::Lines lines;
            int cleared;
        } lines;
        Move move;
    };
};

class EventManager {
    static constexpr int MAX_EVENTS = 16;
    std::vector<Event> events;
    int used;

    public:
        EventManager();
        constexpr bool empty();
        bool nextEvent(Event &event);

        void addEvent(Event::Type);
        void addPieceEvent(Event::Type type, int);
        void addLinesEvent(mutantris::Lines lines, int lines_clared);
        void addMoveEvent(Event::Move move);
};

#endif
