#include "turing.h"
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

    Turing *turing = turing_create(TAPE_SIZE, (State *)marxen_buntrock);

    for (size_t i = 0; i < 50; i++) {
        turing_iterate(turing);
        printf("Step %zu: \n", turing->steps);
        for (size_t i = 0; i < turing->size; i++) {
            printf("%d", turing->tape[i]);
        }
        printf("\n");

        for (size_t i = 0; i < turing->size; i++) {
            if (&turing->tape[i] == turing->head) {
                printf("^");
            } else {
                printf(" ");
            }
        }
        printf("\n\n");
    }
};