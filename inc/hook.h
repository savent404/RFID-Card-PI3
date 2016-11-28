#ifndef _HOOK_H_
#define _HOOK_H_

#ifdef __cplusplus
extern "C" {
#endif

static void usr_config_hook(int argc, char* argv[]);
static void usr_login_hook(void);
static int  usr_permision_hook(void);
static void usr_IO_open(void);


#ifdef __cplusplus
}
#endif

#endif