#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//#define size_of_block 70

void write_strings_into_file(char* name_of_file, char *text[], size_t number_of_strings_in_text){
    FILE *file = fopen(name_of_file, "wb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    for(size_t i = 0; i < number_of_strings_in_text; i++)
        fwrite(text[i], 1, strlen(text[i])+1, file);
    fclose(file);
}