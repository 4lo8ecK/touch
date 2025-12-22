/*
    HIKA-SOFT
    my 'GNU touch' analog 
    VER - 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
    #include <io.h>
    #define F_OK 0
    int file_exsists(const char* filename) {
        return _access(filename, F_OK);
    }
#else
    #include <unistd.h>
    int file_exsists(const char* filename) {
        return access(filename, F_OK);
    }
#endif

#define APP_NAME "touch"

#ifndef VER_MAJOR
    #define VER_MAJOR 1
#endif
#ifndef VER_MINOR
    #define VER_MINOR 0
#endif

const char* VER_CMD = "--version";
const char* VER_CMD_SHORT = "-v";
const char* INFO_CMD = "--info";
const char* INFO_CMD_SHORT = "-i";

void write_file_empty(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    
    if (file){
        fclose(file);
    }
    else {
        file = fopen(filepath, "w");
        fprintf(file, "");
        fclose(file);
    }
}

void print_version() {
    printf("%s %d.%d\n", APP_NAME, VER_MAJOR, VER_MINOR);
}

void print_info() {
    printf(
        "\n\t"
        "Эта утилиту написал \x1b[1m4lo8ecK\x1b[0m\n\n"
        "Наименование:\t%s\n"
        "Версия:\t\t%d.%d\n"
        "\n"
        "Это просто аналог \x1b[3mGNU touch\x1b[0m,\nсозданный для личного использования\n"
        "\n",
        APP_NAME, VER_MAJOR, VER_MINOR);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    if (argc == 1) {
        printf("\x1b[1mНе указано имя для файла\x1b[0m");
        exit(0);
    }

    else if (argc > 1){
        if (argv[1][0] == '-') {
            if (strcmp(argv[1], VER_CMD) == 0 || strcmp(argv[1], VER_CMD_SHORT) == 0) {
                print_version();
                exit(0);
            }
            else if (strcmp(argv[1], INFO_CMD) == 0 || strcmp(argv[1], INFO_CMD_SHORT) == 0) {
                print_info();
                exit(0);
            }
            else {
                printf("Вызвана неизвестная опция");
                exit(0);
            }
        }
        else{
            for (int i = 1; i < argc; i++){
                write_file_empty(argv[i]);
            }
            exit(0);
        }
    }

    return 0;
}
