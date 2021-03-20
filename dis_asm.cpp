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

// функция file_size() возвращает количество ВСЕХ символов, включая \n, \0 и пробелы
// таким образом для получения количества числовых команд выполняем: (file_size(assemble) - 3) / 2
long long size_of_file = (file_size(assemble) - 3) / 2;


dis_asm(assemble, command_list, size_of_file);

fclose(command_list);
fclose(assemble);

return 0;

}