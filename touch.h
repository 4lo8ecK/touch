#define TCH_WINAPI

#ifdef NDEBUG
    #define print(msg)
#else
    #define print(msg) printf("\x1b[33m\x1b[3m\x1b[2m%s\x1b[0m\n", msg)
#endif

#define APP_NAME "touch"

#define VERSION_MAJOR 1
#define VERSION_MINOR 1

#define OPT_MRK '-'
#define WRITE_MRK ">"

#define VER_OPT "--version"
#define VER_OPT_SHORT "-v"

#define INFO_OPT "--info"
#define INFO_OPT_SHORT "-i"

#define HELP_OPT "--help"
#define HELP_OPT_SHORT "-h"

#define APP_RUS "--russian"
#define APP_RUS_SHORT "-ru"

#define APP_ENG "--english"
#define APP_ENG_SHORT "-en"