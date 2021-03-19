#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "assembler.h"

//! всегда менять формат текстового файла на LF вместо CRLF!!!!!!!!!!!!!!!!!!!!!

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("ERROR, expected more arguments\n");
        return -1;
    }

    FILE* command_list = fopen(argv[1], "rb");
    assert(command_list != NULL);
    FILE* assembler = fopen("commands_codes.txt", "wb");
    assert(assembler != NULL);

    fseek(command_list, 0, SEEK_SET);
    long long size_of_file = file_size(command_list);

    char* buf = (char*) calloc(size_of_file + 1, sizeof(char));

    long long res = fread(buf, sizeof(char), size_of_file + 1, command_list);
    assert(res == size_of_file);

    int str_number = FindPoint(buf);

    string* strings = (string*) calloc(str_number, sizeof(string));
    Fill_StringS(buf, strings, size_of_file);


    if (ASM(assembler, strings, str_number) != 0) return -1;

    free(strings);
    free(buf);
    fclose(command_list);
    fclose(assembler);

    return 0;
}

// TODO: написать ассерты