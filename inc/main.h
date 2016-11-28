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

#define STRING_PERMISSION_NORMALUSR "Permission:Usr"
#define STRING_PERMISSION_BLACKUSR  "Permission:BlackUsr\n"
#define BUFFER_SIZE 1024

/* public var 
 */
extern struct config config_info;

/* normal ID information structure
   */
struct info {
    //input num
    int  i_num;

    //output num
    int  o_num;

    //input str
    char src[50];

    //output str
    char out[200];
};

/* Sys config structutre
   */
struct config {

    /* USB event namee
       etc:"/dev/input/event0"
       */
    char input_path[100];

    /* Information output path
       etc:"/home/pi/Documents/outputname"
       */
    char output_path[100];

    /* extern IO opration script
       It's important when open the door
       */
    char shell_path[100];

    /* Blacklist path
       etc:"./cfg/Blacklistname"
       */
    char deny_path[100];
};



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
