#include "turing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Turing *turing_create(size_t size, State *states)
{
    Turing *turing = malloc(sizeof(Turing));

    turing->size = size;
    turing->states = states;
    turing->current_state = 0;
    turing->tape = calloc(size, sizeof(Symbol));
    turing->head = &turing->tape[size / 2 - 1];
    turing->steps = 0;

    return turing;
}

void turing_destroy(Turing *turing)
{
    free(turing->tape);
    free(turing);
}

void turing_expand_tape(Turing *turing, Direction direction)
{
    turing->size *= 2;
    turing->tape = realloc(turing->tape, turing->size * sizeof(Symbol));

    Symbol *old_tape = turing->tape;
    size_t old_size = turing->size / 2;
    Symbol *new_tape = &turing->tape[turing->size / 2];

    memset(new_tape, ZERO, old_size * sizeof(Symbol));

    if (direction == LEFT) {
        memmove(new_tape, old_tape, old_size * sizeof(Symbol));
        memset(old_tape, ZERO, old_size * sizeof(Symbol));
        turing->head = new_tape;
    }
}

void turing_iterate(Turing *turing)
{
    State current = turing->states[turing->current_state];
    Condition condition = *turing->head == ZERO ? current.zero : current.one;

    if (condition.move == HALT) {
        turing->halt = 1;
        return;
    }

    *turing->head = condition.write;
    turing->head += condition.move;
    turing->current_state = condition.state_index;

    if (turing->head == &turing->tape[0]) {
        turing_expand_tape(turing, LEFT);
    } else if (turing->head == &turing->tape[turing->size - 1]) {
        turing_expand_tape(turing, RIGHT);
    }

    turing->steps++;
}

void turing_print_tape(Turing *turing)
{
    for (size_t i = 0; i < turing->size; i++) {
        if (turing->head == &turing->tape[i]) {
            printf("H");
        } else {
            printf("%d", turing->tape[i]);
        }
    }
    printf("\n");
}
