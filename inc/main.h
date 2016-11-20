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
#define FIFO_NAME "/tmp/type_fifo"
#define BUFFER_SIZE 1024
struct info {
    char src[50];
    int  i_num;
    char out[200];
    int  o_num;
};

struct config {
    char input_path[100];
    char output_path[100];
};

static void usr_login(int fd);
static int  info_get(struct info *);
static int  usr_config(struct config *, char *path);
static void *usr_getc(void *);
static void *usr_putc(void *);

/* CONFIG CMD */
#define DEVICE_PATH  "DEV_PATH"
#define OUTFILE_PATH "OUT_PATH"
#endif
