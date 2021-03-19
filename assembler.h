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
    IN        // input data in the consol and push it to the stack
};

//====================================================================================================

struct string { //struct -- string
    char* str;   //pointer to string
    int len;     //length of string
};

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
int Fill_StringS(char* buf, struct string* strings, long long size) {

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

        printf("keyword = %s\n", keyword);

        while (keyword != NULL) {
            if (!strcmp(keyword, "add")) {
                fprintf(assembler, "%d\n", ADD);
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

        i++;                                                       
    }   

    return 0;                                                           
}                                                          