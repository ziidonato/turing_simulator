#include <stdio.h>
#include <string.h>

#define NUM_STATES 5
#define TAPE_SIZE 10

enum direction {
    LEFT = -1,
    RIGHT = 1,
    NONE = 0,
    HALT = 2,
};

enum symbol {
    ZERO = 0,
    ONE = 1,
};

enum write {
    WRITE_ZERO = 0,
    WRITE_ONE = 1,
    WRITE_BLANK = '_',
};

struct condition {
    enum symbol read;
    enum write write;
    enum direction move;
    int state;
};

struct state {
    struct condition zero;
    struct condition one;
};

int main(int, char **)
{
    enum direction directions[] = {LEFT, RIGHT, NONE};
    enum symbol symbols[] = {ZERO, ONE};
    enum write writes[] = {WRITE_ZERO, WRITE_ONE, WRITE_BLANK};

    struct state states[6] = {
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
         {ZERO, WRITE_BLANK, HALT, 5},
         {ONE, WRITE_ZERO, RIGHT, 0},
         },
    };

    size_t current_size = TAPE_SIZE;
    enum symbol tape[current_size];
    memset(tape, ZERO, current_size * sizeof(enum symbol));

    enum symbol *head = &tape[current_size / 2];
    int state = 0;
    int steps = 0;
    int halt = 0;

    for (int i = 0; i < 100; i++) {
        struct state current = states[state];
        printf("State: %d, Head: %d\n", state, head - tape);
        struct condition condition = *head == ZERO ? current.zero : current.one;

        if (condition.write != WRITE_BLANK) {
            *head = condition.write;
        };

        if (condition.move == HALT) {
            halt = 1;
            break;
        }

        printf("move: %d\n", condition.move);
        head += condition.move;
        state = condition.state;
        steps++;

        if (head >= &tape[current_size]) {
            current_size *= 2;
            enum symbol new_tape[current_size];
            memset(new_tape, ZERO, current_size * sizeof(enum symbol));
            memcpy(new_tape + current_size / 4, tape,
                   current_size / 2 * sizeof(enum symbol));
            memcpy(tape, new_tape, current_size * sizeof(enum symbol));
            head = &tape[current_size / 2 - 1];
        }
        // printf("Steps: %d\n", steps);

        for (int i = 0; i < current_size; i++) {
            printf("%d", tape[i]);
        }
        printf("\n");

        for (int i = 0; i < current_size; i++) {
            if (head == &tape[i]) {
                printf("^");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
};