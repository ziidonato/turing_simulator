#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STATES 5
#define TAPE_SIZE 10

const State marxen_buntrock[6] = {
    {
     {ZERO, WRITE_ONE, LEFT, 1},
     {ONE, WRITE_ONE, RIGHT, 2},
     },
    {
     {ZERO, WRITE_ONE, LEFT, 2},
     {ONE, WRITE_ONE, LEFT, 1},
     },
    {
     {ZERO, WRITE_ONE, LEFT, 3},
     {ONE, WRITE_ZERO, RIGHT, 4},
     },
    {
     {ZERO, WRITE_ONE, RIGHT, 0},
     {ONE, WRITE_ONE, RIGHT, 3},
     },
    {
     {ZERO, WRITE_ONE, LEFT, 5},
     {ONE, WRITE_ZERO, RIGHT, 0},
     },
    {
     {ZERO, WRITE_ONE, HALT, 5},
     {ONE, WRITE_ZERO, RIGHT, 0},
     },
};

int main(int, char **)
{

    size_t current_size = TAPE_SIZE;
    Symbol *tape = calloc(current_size, sizeof(Symbol));
    memset(tape, ZERO, current_size * sizeof(Symbol));

    Symbol *head = &tape[current_size / 2];
    int state = 0;
    int steps = 0;
    int halt = 0;

    while (!halt) {
        struct State current = marxen_buntrock[state];
        printf("State: %d, Head: %d\n", state, head - tape);
        struct Condition condition = *head == ZERO ? current.zero : current.one;

        if (condition.move == HALT) {
            halt = 1;
            break;
        }

        *head = condition.write;
        head += condition.move;
        state = condition.state;

        if (head == &tape[0]) {
            current_size *= 2;
            tape = realloc(tape, current_size * sizeof(Symbol));
            memmove(&tape[current_size / 2], &tape[0],
                    current_size / 2 * sizeof(Symbol));
            memset(&tape[0], ZERO, current_size / 2 * sizeof(Symbol));
            head = &tape[current_size / 2];
        } else if (head == &tape[current_size - 1]) {
            current_size *= 2;
            tape = realloc(tape, current_size * sizeof(Symbol));
            memset(&tape[current_size / 2], ZERO,
                   current_size / 2 * sizeof(Symbol));
        }

        steps++;
        printf("Tape: ");
        for (int i = 0; i < current_size; i++) {
            printf("%d", tape[i]);
        }
        printf("\n");
        printf("Steps: %d\n", steps);
    }
};