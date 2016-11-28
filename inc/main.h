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
  * Brief  When System Reset,This func will output_path
           Startup time information to output_path file
  */
static void usr_login(int fd);

/**
  * Brief  get RFID card ID from USB event's string
  * Para @pt see "struct info"
  * retval if input string can't oprate right, return -1
           if string can be oprated, return 1
  */
static int  info_get(struct info *pt);

/**
  * Brief  get config information from a local config file
  * Para @cpt  see "struct config"
  * Para @path file path
  */
static int  usr_config(struct config *cpt, char *path);

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

/**
  * Brief  the oprate of IO 
           "open door" and "check door status"
  * Para @fd_out output door status to a file char.
                 The door status can tell you IF THE
                 DOOR OPEN ? or it can be not opened.
  */
static void IO_open(int fd_out);

/**
  * Brief  Check ID's Permission
  * Para @ID 10-length number as string
  * Retval ID's grade, if  return val < 0, DOOR OPEN deny
           if return >= 0, Sys will open the door
  */
static int  Authentication(char *ID);
/* CONFIG CMD */
#define DEVICE_PATH  "DEV_PATH"
#define OUTFILE_PATH "OUT_PATH"
#define SHELL_PATH   "SHL_PATH"
#define DENY_PATH    "DNY_PATH"
#endif
