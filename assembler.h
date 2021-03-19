#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum COMMANDS {
    END = 0,  // end of programm
    ADD,      // push data to stack
    SUM,      // pop two elements from stack and push to stack sum of this elements
    MUL,      // pop two elements from stack and push to stack multiplication of this elements
    DIV,      // pop two elements from stack and push to stack division of this elements
    OUT,      // pop element from stack and output it to the consol 
    IN,       // input data in the consol and push it to the stack
    PUSH_RAX, // pop value from rax and push in to stack
    PUSH_RBX, // pop value from rbx and push in to stack
    PUSH_RCX, // pop value from rcx and push in to stack
    PUSH_RDX, // pop value from rdx and push in to stack
    POP_RAX,  // pop value from the stack and pusk it to rax
    POP_RBX,  // pop value from the stack and pusk it to rbx
    POP_RCX,  // pop value from the stack and pusk it to rcx
    POP_RDX,  // pop value from the stack and pusk it to rdx
};

//====================================================================================================

typedef struct _string { //struct -- string
    char* str;   //pointer to string
    int len;     //length of string
} string;

//====================================================================================================

//function to catch size of using file
long long file_size(FILE *stream){

    fseek(stream, 0, SEEK_END); //put the pointer to the end of file

    long long a = ftell(stream);

    fseek(stream, 0, SEEK_SET); //return the poiter to the start of file
    return a;
}

//====================================================================================================

//function filling array of structures by strings from using file
int Fill_StringS(char* buf, string* strings, long long size) {

    char* point_1 = 0;
    char* point_2 = buf;

    long long count = 0;

    strings[count].str = buf;

    
    while ((point_1 = strchr(point_2, '\0')) != &(buf[size])) { // size - 1

        strings[count].len = point_1 - point_2 + 1; //fill string length strlen

        ++count;

        strings[count].str = point_1 + 1;
        point_2 = point_1 + 1;
    }

    return 0;
}

//====================================================================================================

//funtion returned count of newlines in using file and turned all symbols '\n' to '\0'
long long FindPoint(char* stream){

    char* point_1 = 0;
    char* point_2 = stream;

    long long i = 1;

    while ((point_1 = strchr(point_2, '\n')) != NULL) {
        *point_1 = '\0';
        ++i;
        point_2 = point_1 + 1;
    }

    return i;
}

//====================================================================================================

int ASM (FILE* assembler, string* strings, long long str_number) {

    int i = 0;                                                     
    char* keyword = NULL;    

    while (i < str_number) {     

        keyword = strtok(strings[i].str, " \n");

        while (keyword != NULL) {
            if (!strcmp(keyword, "add")) {
                fprintf(assembler, "%d\n", ADD);

                keyword = strtok(NULL, " \n");
                fprintf(assembler, "%d\n", atoi(keyword));
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
            else if (!strcmp(keyword, "push")) {
                keyword = strtok(NULL, " \n");

                if (!strcmp(keyword, "rax")) {
                    fprintf(assembler, "%d\n", PUSH_RAX);
                }
                else if (!strcmp(keyword, "rbx")) {
                    fprintf(assembler, "%d\n", PUSH_RBX);
                }
                else if (!strcmp(keyword, "rcx")) {
                    fprintf(assembler, "%d\n", PUSH_RCX);
                }
                else if (!strcmp(keyword, "rdx")) {
                    fprintf(assembler, "%d\n", PUSH_RDX);
                }
            }
            else if (!strcmp(keyword, "pop")) {
                keyword = strtok(NULL, " \n");

                if (!strcmp(keyword, "rax")) {
                    fprintf(assembler, "%d\n", POP_RAX);
                }
                else if (!strcmp(keyword, "rbx")) {
                    fprintf(assembler, "%d\n", POP_RBX);
                }
                else if (!strcmp(keyword, "rcx")) {
                    fprintf(assembler, "%d\n", POP_RCX);
                }
                else if (!strcmp(keyword, "rdx")) {
                    fprintf(assembler, "%d\n", POP_RDX);
                }
            }
            else if (!strcmp(keyword, "in")) {
                fprintf(assembler, "%d\n", IN);
            }
            else {
                printf("Error, unexpected command\n");
                return -1;
            }

            keyword = strtok(NULL, " \n");
        }    

        i++;                                                       
    }   

    return 0;                                                           
}   

//====================================================================================================

int dis_asm(FILE* assemble, FILE* command_list, long long size_of_file) {

    int command = 0;

    while (size_of_file > 0) {

        fscanf(assemble, "%d", &command);

        switch (command) {
            case END :
            {
                fprintf(command_list, "end\n");
                break;
            }
            case ADD :
            {
                fprintf(command_list, "add ");

                size_of_file--;
                fscanf(assemble, "%d", &command);
                fprintf(command_list, "%d\n", command);
                break;
            }
            case SUM :
            {
                fprintf(command_list, "sum\n");
                break;
            }
            case MUL :
            {
                fprintf(command_list, "mul\n");
                break;
            }
            case DIV :
            {
                fprintf(command_list, "div\n");
                break;
            }
            case OUT :
            {
                fprintf(command_list, "out\n");
                break;
            }
            case IN :
            {
                fprintf(command_list, "in\n");
                break;
            }
            case PUSH_RAX :
            {
                fprintf(command_list, "push rax\n");
                break;
            }
            case PUSH_RBX :
            {
                fprintf(command_list, "push rbx\n");
                break;
            }
            case PUSH_RCX :
            {
                fprintf(command_list, "push rcx\n");
                break;
            }
            case PUSH_RDX :
            {
                fprintf(command_list, "push rdx\n");
                break;
            }
            case POP_RAX :
            {
                fprintf(command_list, "pop rax\n");
                break;
            }
            case POP_RBX :
            {
                fprintf(command_list, "pop rbx\n");
                break;
            }
            case POP_RCX :
            {
                fprintf(command_list, "pop rcx\n");
                break;
            }
            case POP_RDX :
            {
                fprintf(command_list, "pop rdx\n");
                break;
            }
            default :
                printf("Error, unexpected command\n");
                exit(-1);
        }

        size_of_file--;
    }

return 0;

}