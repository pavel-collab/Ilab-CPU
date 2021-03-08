#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"

int main() {

    stack stk = {left_canary, NULL, 0, 0, 0, right_canary};

    FILE* command_list = fopen("commands_codes.txt", "rb");
    assert(command_list != NULL);

    stack_construct(&stk, 5);

    int select_act = 0;
    int element = 0;
    int elem_1 = 0;
    int elem_2 = 0;

    while (fscanf(command_list, "%d", &select_act) != 0) {

        switch (select_act) { 
            case 0: 
            {
                printf("completion of working.\n"); 
                return 0;
            } 
            case 1: 
            {
                if (fscanf(command_list, "%d", &element) == 0) {
                    printf("ERROR, no data to push!\n");
                    return -1;
                }
    
                if (stack_push(&stk, element) == 0) { 
                    printf("push compleated successful.\n"); 
                    break; 
                } 
                else { 
                    printf("Error with push.\n"); 
                    break; 
                } 
            }
            case 5: 
            {
                element = stack_pop(&stk); 
                if (element != POISON) { 
                    printf("output element = %d\n", element); 
                    break; 
                } 
                else { 
                    printf("Error with pop.\n"); 
                    break; 
                } 
            }
            case 2:
            {
                elem_1 = stack_pop(&stk);
                elem_2 = stack_pop(&stk);
                elem_1 = elem_1 + elem_2;

                if (stack_push(&stk, elem_1) == 0) { 
                    printf("sum compleated successful.\n"); 
                    break; 
                } 
                else { 
                    printf("Error with sum.\n"); 
                    break; 
                }
            }
            case 3:
            {
                elem_1 = stack_pop(&stk);
                elem_2 = stack_pop(&stk);
                elem_1 = elem_1 * elem_2;

                if (stack_push(&stk, elem_1) == 0) { 
                    printf("mul compleated successful.\n"); 
                    break; 
                } 
                else { 
                    printf("Error with mul.\n"); 
                    break; 
                }
            }
            case 4:
            {
                elem_1 = stack_pop(&stk);
                elem_2 = stack_pop(&stk);
                elem_1 = (int) (elem_2 / elem_1);

                if (stack_push(&stk, elem_1) == 0) { 
                    printf("div compleated successful.\n"); 
                    break; 
                } 
                else { 
                    printf("Error with div.\n"); 
                    break; 
                }
            }
            default: 
                printf("Unexpected error.\n");
                break;
            } 
        }

    fclose(command_list);
    stack_distruct(&stk);

    return 0;
}