#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;  // массив указателей на строки
    size_t count;    // количество строк
} StringArray;

/**
 * Читает файл, в котором строки разделены символом '\0'.
 * Возвращает структуру StringArray. В случае ошибки возвращает {NULL, 0}.
 * Память, выделенную под строки и массив указателей, должен освободить caller.
 */
StringArray read_null_separated_file(const char *filename) {
    StringArray result = {NULL, 0};
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return result;
    }

    // Определяем размер файла
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    if (file_size < 0) {
        fclose(file);
        return result;
    }
    rewind(file);

    // Читаем весь файл в буфер
    char *buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return result;
    }
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        free(buffer);
        fclose(file);
        return result;
    }
    buffer[file_size] = '\0';   // для безопасности
    fclose(file);

    // Подсчёт количества строк
    size_t count = 0;
    for (long i = 0; i < file_size; ++i) {
        if (buffer[i] == '\0') {
            ++count;
        }
    }
    if (file_size > 0 && buffer[file_size - 1] != '\0') {
        ++count;   // последняя строка не завершена нулём
    }

    // Выделяем массив указателей на строки
    char **strings = NULL;
    if (count > 0) {
        strings = (char**)malloc(sizeof(char*) * count);
        if (!strings) {
            free(buffer);
            return result;
        }
    }

    // Разбираем буфер на строки
    size_t str_idx = 0;
    size_t start = 0;
    for (long i = 0; i < file_size; ++i) {
        if (buffer[i] == '\0') {
            size_t len = i - start;
            char *str = (char*)malloc(len + 1);
            if (!str) {
                // Ошибка: освобождаем уже выделенное
                for (size_t j = 0; j < str_idx; ++j) {
                    free(strings[j]);
                }
                free(strings);
                free(buffer);
                return result;
            }
            memcpy(str, buffer + start, len);
            str[len] = '\0';
            strings[str_idx++] = str;
            start = i + 1;
        }
    }
    // Остаток после последнего нуля (если файл не оканчивается нулём)
    if (start < (size_t)file_size) {
        size_t len = file_size - start;
        char *str = (char*)malloc(len + 1);
        if (!str) {
            for (size_t j = 0; j < str_idx; ++j) {
                free(strings[j]);
            }
            free(strings);
            free(buffer);
            return result;
        }
        memcpy(str, buffer + start, len);
        str[len] = '\0';
        strings[str_idx++] = str;
    }

    free(buffer);
    result.strings = strings;
    result.count = count;   // count должно быть равно str_idx
    return result;
}