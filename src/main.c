#include <stdio.h>
#define TAPE_SIZE 100

enum direction
{
    LEFT = -1,
    RIGHT = 1,
    NONE = 0,
};

enum symbol
{
    ZERO = 0,
    ONE = 1,
};

enum write
{
    WRITE_ZERO = 0,
    WRITE_ONE = 1,
    WRITE_BLANK = '_',
};

struct condition
{
    enum symbol read;
    enum write write;
    enum direction move;
    int state;
};

struct state
{
    struct condition zero;
    struct condition one;
};

int main(int, char **)
{
    struct state states[5] = {
        {
            {ZERO, WRITE_ONE, RIGHT, 1},
            {ONE, WRITE_ZERO, RIGHT, 1},
        },
        {
            {ZERO, WRITE_ONE, LEFT, 0},
            {ONE, WRITE_ZERO, LEFT, 2},
        },
        {
            {ZERO, WRITE_ONE, LEFT, 1},
            {ONE, WRITE_ZERO, RIGHT, 4},
        },
        {
            {ZERO, WRITE_ONE, RIGHT, 2},
            {ONE, WRITE_ZERO, LEFT, 3},
        },
        {
            {ZERO, WRITE_BLANK, NONE, 4},
            {ONE, WRITE_BLANK, NONE, 4},
        },
    };

    enum symbol tape[TAPE_SIZE] = {ZERO};

    enum symbol *head = &tape[TAPE_SIZE / 2];
    int state = 0;
    int steps = 0;

    while (state != 4)
    {
        struct state current = states[state];
        struct condition condition = *head == ZERO ? current.zero : current.one;

        if (condition.write != WRITE_BLANK)
        {
            *head = condition.write;
        };

        head += condition.move;
        state = condition.state;
        steps++;
        printf("Steps: %d\n", steps);
    }

    for (int i = 0; i < TAPE_SIZE; i++)
    {
        printf("%d", tape[i]);
    }
};