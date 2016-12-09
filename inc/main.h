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

#include "typedef.h"
#define FIFO_NAME "/tmp/type_fifo"
#define EXTRA_FIFO_NAME "/tmp/sig_fifo"
#define STRING_PERMISSION_NORMALUSR "Permission:Usr"
#define STRING_PERMISSION_BLACKUSR  "Permission:BlackUsr\n"
#define BUFFER_SIZE 1024

/* public var 
 */
extern struct config config_info;


/**
  * Brief  get RFID card ID from USB event's string
  * Para @pt see "struct info"
  * retval if input string can't oprate right, return -1
           if string can be oprated, return 1
  */
static int  info_get(struct info *pt);

/**
  * Brief  a thread to get USB event , then wirte string to 
           FIFO
  */
static void *usr_getc(void *);

/**
  * Brief  a thread to proc data from FIFO, and output to
           usr defined file or stdout
  */
static void *usr_putc(void *);

#endif
