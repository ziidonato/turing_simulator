#include "turing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_STATES 5
#define TAPE_SIZE 10

const State marxen_buntrock[6] = {
    {
     {ZERO, ONE, LEFT, 1},
     {ONE, ONE, RIGHT, 2},
     },
    {
     {ZERO, ONE, LEFT, 2},
     {ONE, ONE, LEFT, 1},
     },
    {
     {ZERO, ONE, LEFT, 3},
     {ONE, ZERO, RIGHT, 4},
     },
    {
     {ZERO, ONE, RIGHT, 0},
     {ONE, ONE, RIGHT, 3},
     },
    {
     {ZERO, ONE, LEFT, 5},
     {ONE, ZERO, RIGHT, 0},
     },
    {
     {ZERO, ONE, HALT, 5},
     {ONE, ZERO, RIGHT, 0},
     },
};

int main(void)
{

    Turing *turing = turing_create(TAPE_SIZE, (State *)marxen_buntrock);

    while (!turing->halt) {
        // for (int i = 0; i < 1000000; i++) {
        turing_iterate(turing);
        // turing_print_tape(turing);
    }
}