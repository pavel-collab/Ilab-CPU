#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "assembler.h"
#include "stack.h"

typedef struct _CPU {
    stack stk;

    unsigned int IP; // указатель на номер команды в потоке

    int rax;         // регистр rax
    int rbx;         // регистр rbx
    int rcx;         // регистр rcx
    int rdx;         // регистр rdx

} CPU;

int CPU_calculation(CPU loc_CPU, FILE* command_list) {

    int select_act = 0;
    int element = 0;
    int elem_1 = 0;
    int elem_2 = 0;

    while (fscanf(command_list, "%d", &select_act) != 0) {

        switch (select_act) { 
            case END: 
            {
                printf("completion of working.\n");
                printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                return 0;
            } 
            case ADD: 
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
            case OUT: 
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
            case SUM:
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
            case MUL:
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
            case DIV:
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
            case IN :
            {
                printf("pleas, input element: ");
                scanf("%d", &element);

                if (stack_push(&(loc_CPU.stk), element) == 0) { 
                    printf("push compleated successful.\n");
                    loc_CPU.IP += 2;
                    break; 
                } 
                else { 
                    printf("Error with in.\n");
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case POP_RAX :
            {
                element = stack_pop(&(loc_CPU.stk)); 
                if (element != POISON) { 
                    loc_CPU.rax = element;
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with pop rax.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case POP_RBX :
            {
                element = stack_pop(&(loc_CPU.stk)); 
                if (element != POISON) { 
                    loc_CPU.rbx = element;
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with pop rbx.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case POP_RCX :
            {
                element = stack_pop(&(loc_CPU.stk)); 
                if (element != POISON) { 
                    loc_CPU.rcx = element;
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with pop rcx.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case POP_RDX :
            {
                element = stack_pop(&(loc_CPU.stk)); 
                if (element != POISON) { 
                    loc_CPU.rdx = element;
                    loc_CPU.IP++;
                    break; 
                } 
                else { 
                    printf("Error with pop rdx.\n"); 
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case PUSH_RAX :
            {
                if (stack_push(&(loc_CPU.stk), loc_CPU.rax) == 0) { 
                    printf("push compleated successful.\n");
                    loc_CPU.IP += 1;
                    break; 
                } 
                else { 
                    printf("Error with push rax.\n");
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case PUSH_RBX :
            {
                if (stack_push(&(loc_CPU.stk), loc_CPU.rbx) == 0) { 
                    printf("push compleated successful.\n");
                    loc_CPU.IP += 1;
                    break; 
                } 
                else { 
                    printf("Error with push rbx.\n");
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case PUSH_RCX :
            {
                if (stack_push(&(loc_CPU.stk), loc_CPU.rcx) == 0) { 
                    printf("push compleated successful.\n");
                    loc_CPU.IP += 1;
                    break; 
                } 
                else { 
                    printf("Error with push rcx.\n");
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            case PUSH_RDX :
            {
                if (stack_push(&(loc_CPU.stk), loc_CPU.rdx) == 0) { 
                    printf("push compleated successful.\n");
                    loc_CPU.IP += 1;
                    break; 
                } 
                else { 
                    printf("Error with push rdx.\n");
                    printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                    break; 
                }
            }
            default: 
                printf("Unexpected error.\n");
                printf("instruction pointer IP = [%d]\n", loc_CPU.IP);
                exit(-1);
            } 
        }

}