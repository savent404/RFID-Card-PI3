#ifndef _HOOK_H_
#define _HOOK_H_

#ifdef __cplusplus
extern "C" {
#endif
/** There are Usr hook 
  */

/**
  * Brief  When System Reset,This func will output_path
           Startup time information to output_path file
  */
static void usr_login_hook(int fd_out);
/**
  * Brief  get config information from a local config file
  * Para @cpt  see "struct config"
  * Para @path file path
  */
static void usr_config_hook(int argc, char* argv[]);
/**
  * Brief  when system reset, system can output somthing information
  * Para @fd_out output file char
  */
static void usr_login_hook(int fd_out);
/**
  * Brief  Check ID's Permission
  * Para @ID 10-length number as string
  * Retval ID's grade, if  return val < 0, DOOR OPEN deny
           if return >= 0, Sys will open the door
  */
static int  usr_permision_hook(char *pt);
/**
  * Brief  the oprate of IO 
           "open door" and "check door status"
  * Para @fd_out output door status to a file char.
                 The door status can tell you IF THE
                 DOOR OPEN ? or it can be not opened.
  */
static void usr_IO_open_hook(int fd_out);

/** There are Example func guide to design
  */

/* private var used in usr_config
 */
#define DEFAULT_CONFIG_PATH "./config"
#define DEFAULT_INPUT_PATH "/dev/input/event1"
#define DEFUALT_OUTPUT_PATH "./out"
#define DEFAULT_SHELL_PATH "./LoginServe.sh"
#define DEFAULT_DENY_PATH  ""
/* CONFIG CMD */
#define DEVICE_PATH  "DEV_PATH"
#define OUTFILE_PATH "OUT_PATH"
#define SHELL_PATH   "SHL_PATH"
#define DENY_PATH    "DNY_PATH"

//called in usr_permision_hook
static int  Authentication(char *ID);

//called in usr_login_hook
static void usr_login(int fd);

//called in usr_config_hook
static int  usr_config(struct config *cpt, char *path);

//called in usr_IO_open_hook
static void IO_open(int fd_out);
#ifdef __cplusplus
}
#endif

#endif