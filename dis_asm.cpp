#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string.h>
#include "assembler.h"

int main(int argc, char* argv[]) {

FILE* assemble = fopen(argv[1], "rb");
assert(assemble != NULL);
FILE* command_list = fopen("commands_codes.txt", "wb");
assert(command_list != NULL);



fclose(command_list);
fclose(assemble);

return 0;

}