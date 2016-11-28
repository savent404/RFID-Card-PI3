#include <main.h>
#include "hook.h"

struct config config_info = {.input_path ="",.output_path = "", .shell_path = ""};
int main(int argc, char *argv[]) {
    int res = -1;
    pthread_t thread_input, thread_output;
    char *str = NULL;
    usr_config_hook(argc, argv);
    
    /* IO init */
    str = (char*)malloc(sizeof(char)*100);
    memset(str, 0, sizeof(char)*100);
    strcpy(str, config_info.shell_path);
    strcat(str, " start");
    system(str);
    free(str);

    /* fifo access */
    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0720);
        if (res != 0) {
            fprintf(stderr, "FIFO create error : %d\n", res);
            fprintf(stdout, "FIFO create error : %d\n", res);
            exit(-1);
        }
    }

    
    //thread create 
    res = pthread_create(&thread_input, NULL, usr_getc, NULL);
    if (res < 0) {
        fprintf(stderr, "Thread create error\n");
        exit(-1);
    }
    res = pthread_create(&thread_output, NULL, usr_putc, NULL);
    if (res < 0) {
        fprintf(stderr, "Thread creat error\n");
        exit(-1);
    }
    
    while (1) {
        sleep(1);
    }
    exit(0);
}

static int  info_get(struct info *pt) {
    time_t T;
    int res = 0;

    // get ID string
    sscanf(pt->src, "%s", pt->out);

    // check ID is right?
    if (strlen(pt->out) != 10) {
        char buf[100];
        strcpy(buf, pt->out);
        strcpy(pt->out, "->Error Parameter: @");
        strcat(pt->out, buf);
        res = -1;
    }
    
    // ID is right
    else {
        strcat(pt->out, "\tLogin at");
        res = 1;
    }// if (strlen(pt->out) != 10)

    // get local time
    time(&T);
    strcat(pt->out, "\t");
    strcat(pt->out, asctime(localtime(&T)));

    //output time information to pt->out
    pt->o_num = strlen(pt->out);
    return res;

}

static void *usr_putc(void* null) {
    
    char buf = 0;
    struct info F;
    int std_out = STDOUT_FILENO;
    int in = open(FIFO_NAME, O_RDONLY);
    if (strlen(config_info.output_path) != 0) {
        std_out = open(config_info.output_path, O_WRONLY|O_APPEND|O_CREAT);
        if (std_out < 0) {
        fprintf(stderr, "Open Type Err:%d -> %s\n", std_out, config_info.output_path);
        fprintf(stderr, "Open Type Err:%d -> %s\n", std_out, config_info.output_path);
            exit(-1);
        }
    }
    if (in < 0) {
        perror("open fifo error");
        close(std_out);
        exit(-1);
    }
    
    /* usr info */
    usr_login_hook(std_out);

    while (1) {
	    buf = 0;
        F.i_num = 0;
        F.o_num = 0;
        memset(F.src, 0, 50);
        memset(F.out, 0, 200);

        while (buf != '\n') {
            if (read(in, &buf, 1) == 1)
                F.src[F.i_num++] = buf;
        }
	
        /* if ID is iligeal, it will not check in Authentication
           and IO_open func */
        if (info_get(&F) < 0) {
            write(std_out, F.out, F.o_num);
            continue;
        }
        else {
            write(std_out, F.out, F.o_num);
            if (usr_permision_hook(F.src) >= 0) {
                write(std_out, STRING_PERMISSION_NORMALUSR, sizeof(STRING_PERMISSION_NORMALUSR));
                usr_IO_open_hook(std_out);
            }
            else {
                write(std_out, STRING_PERMISSION_BLACKUSR, sizeof(STRING_PERMISSION_BLACKUSR));
            }
        }
	sleep(1);
    }
    exit(-1);
}

static void *usr_getc(void *null) {
    char buf = 0;
    struct input_event t;
    int fd = open(config_info.input_path, O_RDONLY);
    int out = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Open Type Err:%d -> %s\n", fd, config_info.input_path);
        fprintf(stderr, "Open Type Err:%d -> %s\n", fd, config_info.input_path);
        exit(-1);
    }
    if (out < 0) {
        perror("open fifo error");
        close(fd);
        exit(-1);
    }
    while (1) {
        if (read(fd, &t, sizeof(t)) == sizeof(t)) {
            if (t.type == 1 && t.value == 1) {
                switch(t.code) {
                    case KEY_0:
                        buf = '0';
                        break;
                    case KEY_1:
                        buf = '1';
                        break;
                    case KEY_2:
                        buf = '2';
                        break;
                    case KEY_3:
                        buf = '3';
                        break;
                    case KEY_4:
                        buf = '4';
                        break;
                    case KEY_5:
                        buf = '5';
                        break;
                    case KEY_6:
                        buf = '6';
                        break;
                    case KEY_7:
                        buf = '7';
                        break;
                    case KEY_8:
                        buf = '8';
                        break;
                    case KEY_9:
                        buf = '9';
                        break;
                    case KEY_A:
                        buf = 'A';
                        break;
                    case KEY_B:
                        buf = 'B';
                        break;
                    case KEY_C:
                        buf = 'C';
                        break;
                    case KEY_D:
                        buf = 'D';
                        break;
                    case KEY_E:
                        buf = 'E';
                        break;
                    case KEY_F:
                        buf = 'F';
                        break;
                    case KEY_SPACE:
                        buf = ' ';
                        break;
                    case KEY_ENTER:
                        buf = '\n';
                        break;
                    default:
                        buf = '\0';
                        break;
                } if (buf) {
                    write(out, &buf, 1);
		}  buf = 0;
            }
        }
    }
    exit(-1);
}
