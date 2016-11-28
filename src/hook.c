#include "hook.h"
#include <main.h>

static void usr_config_hook(int argc, char* argv[]);
static void usr_login_hook(void);
static int  usr_permision_hook(char *pt) {
    //example func
    return Authentication(pt);
}
static void usr_IO_open(void);