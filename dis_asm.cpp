#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string.h>
#include "assembler.h"

int main(int argc, char* argv[]) {

FILE* assemble = fopen(argv[1], "rb");
assert(assemble != NULL);
FILE* command_list = fopen("disassembled_code.txt", "wb");
assert(command_list != NULL);

long long size_of_file = file_size(assemble);

printf("size_of_file = %lli", size_of_file);

dis_asm(assemble, command_list, size_of_file);

fclose(command_list);
fclose(assemble);

return 0;

}