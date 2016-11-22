#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#define DEFAULT_CONFIG_PATH "./config"
#define DEFAULT_INPUT_PATH "/dev/input/event1"
#define DEFUALT_OUTPUT_PATH "./out"
#define DEFAULT_SHELL_PATH "./LoginServe.sh"
#define DEFAULT_DENY_PATH  ""
#define FIFO_NAME "/tmp/type_fifo"

#define STRING_PERMISSION_NORMALUSR "Permission:Usr"
#define STRING_PERMISSION_BLACKUSR  "Permission:BlackUsr\n"
#define BUFFER_SIZE 1024
struct info {
    int  i_num;
    int  o_num;
    char src[50];
    char out[200];
};

struct config {
    char input_path[100];
    char output_path[100];
    char shell_path[100];
    char deny_path[100];
};

static void usr_login(int fd);
static int  info_get(struct info *);
static int  usr_config(struct config *, char *path);
static void *usr_getc(void *);
static void *usr_putc(void *);
static void IO_open(int fd_out);
static int  Authentication(char *);
/* CONFIG CMD */
#define DEVICE_PATH  "DEV_PATH"
#define OUTFILE_PATH "OUT_PATH"
#define SHELL_PATH   "SHL_PATH"
#define DENY_PATH    "DNY_PATH"
#endif
