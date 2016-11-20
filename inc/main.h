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

#define FIFO_NAME "/tmp/type_fifo"
#define BUFFER_SIZE 1024
struct info {
    char src[50];
    int  i_num;
    char out[200];
    int  o_num;
};

static void usr_login(void);
static int  info_get(struct info *);
static void *usr_getc(void *);
static void *usr_putc(void *);

#endif
