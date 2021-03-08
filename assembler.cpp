#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "commands.h"

//! всегда менять формат текстового файла на LF вместо CRLF!!!!!!!!!!!!!!!!!!!!!

int main() {

    FILE* command_list = fopen("commands.txt", "rb");
    assert(command_list != NULL);
    FILE* assembler = fopen("commands_codes.txt", "wb");
    assert(assembler != NULL);

    // переменная, куда записывается прочитанная строка из файла
    char string[20];
    // указатель, в который будет помещен адрес массива, в который прочитана строка 
    // (фактически адрес переменной string) или NULL
    char* estr = fgets(string, 20, command_list);

    char* keyword = NULL;
    int i = 0;

    while (estr != NULL) {
        keyword = strtok(string, " \n");

        while (keyword != NULL) {
            if (!strcmp(keyword, "push")) {
                fprintf(assembler, "%d\n", PUSH);
            }
            else if (!strcmp(keyword, "sum")) {
                fprintf(assembler, "%d\n", SUM);
            }
            else if (!strcmp(keyword, "mul")) {
                fprintf(assembler, "%d\n", MUL);
            }
            else if (!strcmp(keyword, "div")) {
                fprintf(assembler, "%d\n", DIV);
            }
            else if (!strcmp(keyword, "out")) {
                fprintf(assembler, "%d\n", OUT);
            }
            else if (!strcmp(keyword, "end")) {
                fprintf(assembler, "%d\n", END);
            }
            else {
                fprintf(assembler, "%d\n", atoi(keyword));
            }

            keyword = strtok(NULL, " \n");
        }

        estr = fgets(string, 20, command_list);
    }

    fclose(command_list);
    fclose(assembler);

    return 0;
}

// TODO: написать ассерты
// TODO: написать тело CPU, подумать, как связать это с файлом stck