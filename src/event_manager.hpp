#ifndef _EVENT_MANAGER_HPP_
#define _EVENT_MANAGER_HPP_

#include <vector>
#include "mutantris.hpp"

/**
 * Events
 *
 * Game Over
 * Pause
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
        PAUSE,
        GAME_OVER,
        GAME_TICK,
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
        mutantris::Piece piece;
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
        void addPieceEvent(Event::Type type, mutantris::Piece piece);
        void addLinesEvent(mutantris::Lines lines, int lines_clared);
        void addMoveEvent(Event::Move move);
};

#endif
