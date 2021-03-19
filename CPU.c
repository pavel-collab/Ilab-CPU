#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "CPU.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("ERROR, expected more arguments\n");
        return -1;
    }

    stack stk = {left_canary, NULL, 0, 0, 0, right_canary};
    CPU loc_CPU = {stk, 0, 0, 0, 0, 0};

    FILE* command_list = fopen(argv[1], "rb");
    assert(command_list != NULL);

    stack_construct(&(loc_CPU.stk), 5);

    CPU_calculation(loc_CPU, command_list);

    fclose(command_list);
    stack_distruct(&(loc_CPU.stk));

    return 0;
}