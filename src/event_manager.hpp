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
        PIECE_MOVES,
        PIECE_DROPPED,
        PIECE_ROTATES,
        PIECE_MUTATES,
        CLEAR_LINE,
    } type;
    enum Move {
        LEFT,
        RIGHT,
        DROP
    };
    union {
        mutantris::Piece piece;
        int lines;
        Move move;
    };
};

class EventManager {
    static constexpr int MAX_EVENTS = 8;
    std::vector<Event> events;
    int used;

    public:
        EventManager();
        constexpr bool empty();
        bool nextEvent(Event &event);

        void addPieceEvent(Event::Type type, mutantris::Piece piece);
        void addLineEvent(int lines);
        void addMoveEvent(Event::Move move);
};
