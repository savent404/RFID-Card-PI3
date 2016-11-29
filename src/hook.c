#include "hook.h"
#include <main.h>


/** There are Usr hook 
  */
static void usr_login_hook(int fd_out) {
    //example
    usr_login(fd_out);

    //usr login
}
static void usr_config_hook(int argc, char* argv[]) {
    //example
    if (argc != 1) {
        for (int i = 1; i < argc; i++) {
            // Para: help
            if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
                fprintf(stdout, "There is no help, help yourself\n");
                return 0;
            }
            // Para: -config 
            if (!strcmp(argv[i], "-config")) {
                i += 1;
                if (argc <= i) {
                    // use default path:"./config" 
                    if (usr_config(&config_info, DEFAULT_CONFIG_PATH))
                        return -1;
                }
                else {
                    if (usr_config(&config_info, argv[i]))
                        return -1;
                }
            }
        }
    }

    //usr config
}
static int  usr_permision_hook(char *pt) {
    //example func
    return Authentication(pt);

    //usr permision check

}
static void usr_IO_open_hook(int fd_out) {
    //example func
    IO_open(fd_out);

    //usr Open
}


/** There are Example func guide to design
  */
static void usr_login(int fd) {
    time_t t;
    time(&t);
    char buf[100] = "##System Login:    ";
    strcat(buf, asctime(localtime(&t)));
    write(fd, buf, strlen(buf));
}
static int  Authentication(char *pt) {
    char buf[100];
    //search from blacklist
    sscanf(pt, "%s", pt);
    int black_fd = open(config_info.deny_path, O_RDONLY);
    if (black_fd >= 0) {
       while (read(black_fd, buf, 11) >= 10) {
           sscanf(buf, "%s", buf);
           /* test info */
           if (!strcmp(buf, pt)) {
               close(black_fd);
               return -1;
           }
       }
    }
    else {
        return 0;
    }
    close(black_fd);
    return 0;
}
static int  usr_config(struct config *t, char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Open config file Err:%d :%s\n", fd, path);
        fprintf(stdout, "Open config file Err:%d :%s\n", fd, path);
        return -1;
    }

    int cnt = 0, line_cnt = 0;
    char buf[200];
    char *pt = buf;
    char line_buf[100];
    char name[100], para[100];
    cnt = read(fd, buf, 200);

    t->input_path[0]  = 0;
    t->output_path[0] = 0;
    t->shell_path[0]  = 0;
    t->deny_path[0]   = 0;

    while (cnt) {
        while (cnt > 0&& pt[line_cnt] != '\n') {
            line_cnt += 1;
            cnt -= 1;
        }
        if (pt[line_cnt] == '\n') {
            cnt -= 1;
            line_cnt += 1;
        }
        sscanf(pt, "%s = %s", name, para);
        if (!strcmp(name, DEVICE_PATH)) {
            strcpy(t->input_path, para);
        }
        else if (!strcmp(name, OUTFILE_PATH)) {
            strcpy(t->output_path, para);
        }
        else if (!strcmp(name, SHELL_PATH)) {
            strcpy(t->shell_path, para);
        }
        else if (!strcmp(name, DENY_PATH)) {
            strcpy(t->deny_path, para);
        }
        pt += line_cnt;
        line_cnt = 0;
    }

    if (strlen(t->input_path) == 0)
        strcpy(t->input_path, DEFAULT_INPUT_PATH);
    if (strlen(t->output_path) == 0)
        strcpy(t->output_path, DEFUALT_OUTPUT_PATH);
    if (strlen(t->shell_path) == 0)
        strcpy(t->shell_path, DEFAULT_SHELL_PATH);
    if (strlen(t->deny_path) == 0)
        strcpy(t->deny_path, DEFAULT_DENY_PATH);

    close(fd);
    return 0;
}

static void IO_open(int fd_out) {
    
    char buf[100];

    /* call LoginServe.sh */
    strcpy(buf, config_info.shell_path);
    strcat(buf, " open >>");
    strcat(buf, config_info.output_path);
    system(buf);

    strcpy(buf, config_info.shell_path);
    strcat(buf, " check >>");
    strcat(buf, config_info.output_path);
    system(buf);
    /* target reset */
//    dup2(old_fd, STDOUT_FILENO);
}