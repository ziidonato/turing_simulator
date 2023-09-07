#pragma once
#include <stddef.h>
#include <stdint.h>

typedef enum Direction {
    LEFT = -1,
    RIGHT = 1,
    NONE = 0,
    HALT = 2,
} Direction;

typedef enum Symbol {
    ZERO = 0,
    ONE = 1,
} Symbol;

typedef struct Condition {
    Symbol read;
    Symbol write;
    Direction move;
    size_t state_index;
} Condition;

typedef struct State {
    Condition zero;
    Condition one;
} State;

typedef struct Turing {
    size_t current_state;
    Symbol *head;
    size_t size;
    size_t steps;
    State *states;
    Symbol *tape;
    uint8_t halt;
} Turing;

Turing *turing_create(size_t size, State *states);
void turing_destroy(Turing *turing);
void turing_expand_tape(Turing *turing, Direction direction);
void turing_iterate(Turing *turing);
void turing_print_tape(Turing *turing);
State *turing_parse_states(const char *states);