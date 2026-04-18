#include <stddef.h>

typedef struct {
    char **strings;  // массив указателей на строки
    size_t count;    // количество строк
} StringArray;

StringArray read_null_separated_file(const char *filename);