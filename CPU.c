#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"

// TODO: реализовать загрузку и извлечение данных в регистр
// TODO: стелать jmp (функция переноса коретки в файле)

typedef struct _CPU {
    stack stk;
    unsigned int IP; // указатель на номер команды в потоке
    int rax; // регистр
} CPU;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("ERROR, expected more arguments\n");
        return -1;
    }

    stack stk = {left_canary, NULL, 0, 0, 0, right_canary};
    CPU loc_CPU = {stk, 0, 0};

    FILE* command_list = fopen(argv[1], "rb");
    assert(command_list != NULL);

    stack_construct(&(loc_CPU.stk), 5);

    int select_act = 0;
    int element = 0;
    int elem_1 = 0;
    int elem_2 = 0;

    while (fscanf(command_list, "%d", &select_act) != 0) {

        switch (select_act) { 
            case 0: 
            {
                printf("completion of working.\n");
                printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                return 0;
            } 
            case 1: 
            {
                if (fscanf(command_list, "%d", &element) == 0) {
                    printf("ERROR, no data to push!\n");
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    return -1;
                }
    
                if (stack_push(&(loc_CPU.stk), element) == 0) { 
                    printf("push compleated successful.\n");
                    loc_CPU.IP += 2;
                    break; 
                } 
                else { 
                    printf("Error with push.\n");
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                } 
            }
            case 5: 
            {
                element = stack_pop(&(loc_CPU.stk)); 
                if (element != POISON) { 
                    printf("output element = %d\n", element);
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with pop.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                } 
            }
            case 2:
            {
                elem_1 = stack_pop(&(loc_CPU.stk));
                elem_2 = stack_pop(&(loc_CPU.stk));
                elem_1 = elem_1 + elem_2;

                if (stack_push(&(loc_CPU.stk), elem_1) == 0) { 
                    printf("sum compleated successful.\n");
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with sum.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case 3:
            {
                elem_1 = stack_pop(&(loc_CPU.stk));
                elem_2 = stack_pop(&(loc_CPU.stk));
                elem_1 = elem_1 * elem_2;

                if (stack_push(&(loc_CPU.stk), elem_1) == 0) { 
                    printf("mul compleated successful.\n");
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with mul.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case 4:
            {
                elem_1 = stack_pop(&(loc_CPU.stk));
                elem_2 = stack_pop(&(loc_CPU.stk));
                elem_1 = (int) (elem_2 / elem_1);

                if (stack_push(&(loc_CPU.stk), elem_1) == 0) { 
                    printf("div compleated successful.\n");
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with div.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            default: 
                printf("Unexpected error.\n");
                printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                break;
            } 
        }

    fclose(command_list);
    stack_distruct(&(loc_CPU.stk));

    return 0;
}