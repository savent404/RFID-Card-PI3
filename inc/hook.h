#ifndef _HOOK_H_
#define _HOOK_H_

#ifdef __cplusplus
extern "C" {
#endif

static void usr_config_hook(int argc, char* argv[]);
static void usr_login_hook(void);
/**
  * Brief  Check ID's Permission
  * Para @ID 10-length number as string
  * Retval ID's grade, if  return val < 0, DOOR OPEN deny
           if return >= 0, Sys will open the door
  */
static int  usr_permision_hook(char *pt);
static void usr_IO_open(void);


#ifdef __cplusplus
}
#endif

#endif