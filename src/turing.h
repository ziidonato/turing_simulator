#pragma once
#include <stddef.h>

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

typedef enum Write {
    WRITE_ZERO = 0,
    WRITE_ONE = 1,
} Write;

typedef struct Condition {
    Symbol read;
    Write write;
    Direction move;
    size_t state_index;
} Condition;

typedef struct State {
    Condition zero;
    Condition one;
} State;

typedef struct Turing {
    size_t current_state;
    size_t head;
    size_t size;
    size_t steps;
    State *states;
    Symbol *tape;
} Turing;

Turing *turing_create(size_t size);
void turing_destroy(Turing *turing);