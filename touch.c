#if 0
/*
    HIKA-SOFT
    my 'GNU touch' analog 
    VER - 1.0
*/
#endif

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "touch.h"

#define EN_LANG 0
#define RU_LANG 1

int APP_LANG = RU_LANG;
char* ui_lang[] = {"English", "Русский"};

#define LANG_FILE "lang.dat"

int file_exsist(const char* path) {
    FILE* fl = fopen(path, "r");
    if (fl){
        return 1;
    }
    return 0;
}

void write_file(const char* path, const char* content) {
    FILE* file = fopen(path, "w");
    fprintf(file, content);
    fclose(file);
}

void write_file_bin(const char* path, const char* dat) {
    FILE* file = fopen(path, "wb");
    fwrite(dat, sizeof(char), strlen(dat), file);
    fclose(file);
}

const char* read_file(const char* path) {
    FILE* fl = fopen(path, "r");
    if (!fl) { return NULL;}
    fseek(fl, 0, SEEK_END);
    int len = ftell(fl);
    fseek(fl, 0, SEEK_SET);

    char* dat = malloc(len + 1);
    fread(dat, len, 1, fl);
    fclose(fl);

    dat[len] = '\0';
    return dat;
}

void change_lang(int lang) {
    if (lang == EN_LANG) {
        APP_LANG = EN_LANG;
        write_file_bin(LANG_FILE, APP_ENG_SHORT);
    }
    else if (lang == RU_LANG) {
        APP_LANG = EN_LANG;
        write_file_bin(LANG_FILE, APP_RUS_SHORT);
    }
}

void init_lang_dat() {

    if (file_exsist(LANG_FILE)) {
        const char* dat = read_file(LANG_FILE);
        if (strcmp(dat, APP_ENG_SHORT) == 0) {
            APP_LANG = EN_LANG;
        }
        else if (strcmp(dat, APP_RUS_SHORT) == 0) {
            APP_LANG = RU_LANG;
        }
        else {
            change_lang(RU_LANG);
        }
    }
    else {
        change_lang(RU_LANG);
    }
}

void print_info() {
    if (APP_LANG == EN_LANG) {
        printf(
        "\n\t\x1b[1m\x1b[33m%s\x1b[0m utility is written by \x1b[1m4lo8ecK\x1b[0m\n"
        "\t\x1b[1m\x1b[2m------------------------------------\x1b[0m\n"
        "\t\x1b[3mVersion:\x1b[0m\t%d.%d\n"
        "\t\x1b[3mLanguage:\x1b[0m\t%s\n\n"
        "\n",
        APP_NAME, VERSION_MAJOR, VERSION_MINOR, ui_lang[APP_LANG]
        );
    }
    else if (APP_LANG == RU_LANG) {
        printf(
        "\n\t\x1b[1m\x1b[33m%s\x1b[0m утилиту написал \x1b[1m4lo8ecK\x1b[0m\n"
        "\t\x1b[1m\x1b[2m-----------------------------\x1b[0m\n"
        "\t\x1b[3mВерсия:\x1b[0m\t%d.%d\n"
        "\t\x1b[3mЯзык:\x1b[0m\t%s\n"
        "\n",
        APP_NAME, VERSION_MAJOR, VERSION_MINOR, ui_lang[APP_LANG]
        );
    }
}

void print_version() {
    printf("%s: %d.%d", APP_NAME, VERSION_MAJOR, VERSION_MINOR);
}

void unknown_option(const char* opt) {
    if (APP_LANG == EN_LANG) {
        printf("Unknown option \x1b[33m\x1b[3m%s\x1b[0m\n", opt);
    }
    else if (APP_LANG == RU_LANG) {
        printf("Неизвестная опция \x1b[33m\x1b[3m%s\x1b[0m\n", opt);
    }
}

void call_option(const char* option) {
    //
    if (strcmp(option, VER_OPT) == 0 || strcmp(option, VER_OPT_SHORT) == 0) {
        print_version();
    }
    else if (strcmp(option, INFO_OPT) == 0 || strcmp(option, INFO_OPT_SHORT) == 0) {
        print_info();
    }
    else if (strcmp(option, APP_ENG) == 0 || strcmp(option, APP_ENG_SHORT) == 0) {
        change_lang(EN_LANG);
    }
    else if (strcmp(option, APP_RUS) == 0 || strcmp(option, APP_RUS_SHORT) == 0) {
        change_lang(RU_LANG);
    }
    else {
        unknown_option(option);
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, ".UTF-8");

    for (int i = 1; i < argc; i++) {
        
        if (argv[i][0] == OPT_MRK) {
            print("Вызана опция");
            init_lang_dat();
            call_option(argv[i]);
        }
        else {
            write_file(argv[i], NULL);
        }
    }
}
