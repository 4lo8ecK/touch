#if 0
/*
    HIKA-SOFT
    my 'GNU touch' analog 
    VER - 1.1
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

#define LANG_FILE_NAME "lang"
#define LANG_FILE_EXT "dat"

const char* get_executable_dir(const char* filename, const char* ext) {
    char* path = (char*)malloc(MAX_PATH);
    DWORD count = GetModuleFileNameA(NULL, path, MAX_PATH);
    if (count == 0) {
        return NULL;
    }

    char* drive = (char*)malloc(_MAX_DRIVE);
    char* dir = (char*)malloc(_MAX_DIR);
    
    _splitpath_s(path, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
    _makepath_s(path, MAX_PATH, drive, dir, filename, ext);
    
    free(drive);
    free(dir);
    
    return path;
}

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

void change_lang(const char* path, int lang) {
    if (lang == EN_LANG) {
        APP_LANG = EN_LANG;
        write_file_bin(path, APP_ENG_SHORT);
    }
    else if (lang == RU_LANG) {
        APP_LANG = RU_LANG;
        write_file_bin(path, APP_RUS_SHORT);
    }
}

void init_lang_dat() {
    const char* path_to_exe = get_executable_dir(LANG_FILE_NAME, LANG_FILE_EXT);
    print(path_to_exe);
    if (file_exsist(path_to_exe)) {
        
        const char* dat = read_file(path_to_exe);
        if (strcmp(dat, APP_ENG_SHORT) == 0) {
            APP_LANG = EN_LANG;
        }
        else if (strcmp(dat, APP_RUS_SHORT) == 0) {
            APP_LANG = RU_LANG;
        }
        else {
            change_lang(path_to_exe, RU_LANG);
        }
    }
    else {
        change_lang(path_to_exe, RU_LANG);
    }
}

void print_info() {
    if (APP_LANG == EN_LANG) {
        printf(
        "\n\t\x1b[1;33m%s\x1b[0m utility is written by \x1b[1m4lo8ecK\x1b[0m\n"
        "\t\x1b[1m\x1b[2m------------INFO-------------\x1b[0m\n"
        "\t\x1b[3mVersion:\x1b[0m\t%d.%d\n"
        "\t\x1b[3mLanguage:\x1b[0m\t%s\n\n"
        "\n"
        "\t\x1b[1;33m-h\x1b[0;3m or \x1b[0;1;33m--help\x1b[0;3m for additional information\x1b[0m\n"
        "\n",
        APP_NAME, VERSION_MAJOR, VERSION_MINOR, ui_lang[APP_LANG]
        );
    }
    else if (APP_LANG == RU_LANG) {
        printf(
        "\n\t\x1b[1;33m%s\x1b[0m утилиту написал \x1b[1m4lo8ecK\x1b[0m\n"
        "\n"
        "\t\x1b[1m\x1b[2m---------ИНФОРМАЦИЯ----------\x1b[0m\n"
        "\t\x1b[3mВерсия:\x1b[0m\t%d.%d\n"
        "\t\x1b[3mЯзык:\x1b[0m\t%s\n"
        "\n"
        "\t\x1b[1;33m-h\x1b[0;3m или \x1b[0;1;33m--help\x1b[0;3m для дополнительной информации\x1b[0m\n"
        "\n",
        APP_NAME, VERSION_MAJOR, VERSION_MINOR, ui_lang[APP_LANG]
        );
    }
}

void print_version() {
    printf("%s: %d.%d", APP_NAME, VERSION_MAJOR, VERSION_MINOR);
}

void print_help() {
    print_info();
    
    if (APP_LANG == EN_LANG) {
        printf(
        "\t\x1b[1;2m------------USAGE------------\x1b[0m\n"
        "\tThe order of arguments is unimportant\n"
        "\t|> \x1b[33mtouch\x1b[0m \x1b[1m[<filename> ...]\x1b[0m - create new files \x1b[2;3m(count of arguments is unlimited)\x1b[0m\n"
        "\n\t\x1b[3;1mOptions:\x1b[0m\n"
        "\t|> \x1b[33mtouch\x1b[0m \x1b[1m[-v | --version] [-i | --info] [-h | --help]\x1b[0m\n"
        "\t|> \x1b[33mtouch\x1b[0m \x1b[1m[-ru | --russian] [-en | --english]\x1b[0m\n"
        "\n"
        "\t\x1b[1m-v | --version\x1b[0m\t- show version\n"
        "\t\x1b[1m-i | --info\x1b[0m\t- show information\n"
        "\t\x1b[1m-h | --help\x1b[0m\t- show help \x1b[2;3m(I know, this is useless here)\x1b[0m\n"
        "\n"
        "\t\x1b[1m-ru | --russian\x1b[0m\t- set language to \x1b[1;4mRussian\x1b[0m\n"
        "\t\x1b[1m-en | --english\x1b[0m\t- set language to \x1b[1;4mEnglish\x1b[0m\n"
        "\n");
    }
    else if (APP_LANG == RU_LANG) {
        printf(
        "\t\x1b[1;2m--------ИСПОЛЬЗОВАНИЕ--------\x1b[0m\n"
        "\tПорядок аргументов неважен\n"
        "\t|> \x1b[33mtouch\x1b[0m \x1b[1m[<наименование файла> ...]\x1b[0m - создание файлов \x1b[2;3m(количество аргументов не ограничено)\x1b[0m\n"
        "\n\t\x1b[3;1mОпции:\x1b[0m\n"
        "\t|> \x1b[33mtouch\x1b[0m \x1b[1m[-v | --version] [-i | --info] [-h | --help]\x1b[0m\n"
        "\t|> \x1b[33mtouch\x1b[0m \x1b[1m[-ru | --russian] [-en | --english]\x1b[0m\n"
        "\n"
        "\t\x1b[1m-v | --version\x1b[0m\t- показать версию\n"
        "\t\x1b[1m-i | --info\x1b[0m\t- показать информацию\n"
        "\t\x1b[1m-h | --help\x1b[0m\t- показать доп. информацию \x1b[2;3m(Знаю-знаю, отображение \x1b[0;2;33mhelp\x1b[0;2;3m здесь уже не нужно, но всё равно, оно здесь по-приколу)\x1b[0m\n"
        "\n"
        "\t\x1b[1m-ru | --russian\x1b[0m\t- установить \x1b[1;4mрусский\x1b[0m язык\n"
        "\t\x1b[1m-en | --english\x1b[0m\t- установить \x1b[1;4mанглийский\x1b[0m язык\n"
        "\n");
    }
}

void unknown_option(const char* opt) {
    if (APP_LANG == EN_LANG) {
        printf("Unknown option \x1b[33;3m%s\x1b[0m\nTry \x1b[1;33m-h\x1b[0m or \x1b[1;33m--help\x1b[0m for additional information\n", opt);
    }
    else if (APP_LANG == RU_LANG) {
        printf("Неизвестная опция \x1b[33;3m%s\x1b[0m\nПопробуйте использовать \x1b[1;33m-h\x1b[0m или \x1b[1;33m--help\x1b[0m для доп. информации", opt);
    }
}

void call_option(const char* option) {
    //
    const char* path_to_exe = get_executable_dir(LANG_FILE_NAME, LANG_FILE_EXT);

    if (strcmp(option, VER_OPT) == 0 || strcmp(option, VER_OPT_SHORT) == 0) {
        print_version();
    }
    else if (strcmp(option, INFO_OPT) == 0 || strcmp(option, INFO_OPT_SHORT) == 0) {
        print_info();
    }
    else if (strcmp(option, HELP_OPT) == 0 || strcmp(option, HELP_OPT_SHORT) == 0) {
        print_help();
    }
    else if (strcmp(option, APP_ENG) == 0 || strcmp(option, APP_ENG_SHORT) == 0) {
        change_lang(path_to_exe, EN_LANG);
    }
    else if (strcmp(option, APP_RUS) == 0 || strcmp(option, APP_RUS_SHORT) == 0) {
        change_lang(path_to_exe, RU_LANG);
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
