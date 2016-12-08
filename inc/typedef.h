#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
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

#endif
