#include <main.h>

void usr_login(void) {
    time_t T;
    char buf[100] = "##System Login:    ";
    strcat(buf, asctime(localtime(&T)));
    write(STDOUT_FILENO, buf, strlen(buf));
}


int  info_get(struct info *pt) {
    time_t T;
    sscanf(pt->src, "%s", pt->out);
    if (strlen(pt->out) != 4) {
        char buf[100];
        strcpy(buf, pt->out);
        strcpy(pt->out, "->Error Parameter: @");
        strcat(pt->out, buf);
    }
    else {
        strcat(pt->out, "\tLogin at");
    }
    time(&T);
    strcat(pt->out, "\t");
    strcat(pt->out, asctime(localtime(&T)));
    pt->o_num = strlen(pt->out);
    return 0;

}

void *usr_putc(void* null) {
    int in = open(FIFO_NAME, O_RDONLY);
    char buf = 0;
    struct info F;

    if (in < 0) {
        perror("open fifo error");
        exit(-1);
    }

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
	
        info_get(&F);
        write(STDOUT_FILENO, F.out, F.o_num);
	
    }
    exit(-1);
}
int main(int argc, char *argv[]) {
    int res = -1;
    pthread_t thread_input, thread_output;
    int type_fd = STDIN_FILENO;
    char buf[30] = "/dev/input/";

    /* usr info */
    usr_login();
    
    /* open type file */
    if (argc == 1)
        type_fd = open("/dev/input/event1", O_RDONLY);
    else {
        strcat(buf, argv[1]);
        type_fd = open(buf, O_RDONLY);
    }
    if (type_fd < 0) {
        fprintf(stderr, "TYPE open error \n");
        exit(-1);
    }

    /* fifo access */
    if (access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "FIFO create error : %d\n", res);
            exit(-1);
        }
    }

    /* thread create */
    res = pthread_create(&thread_input, NULL, usr_getc, &type_fd);
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

    }
    close(type_fd);
    exit(0);
}


void *usr_getc(void *fd) {
    char buf = 0;
    struct input_event t;
    int out = open(FIFO_NAME, O_WRONLY);
    if (out < 0) {
        perror("open fifo error");
        exit(-1);
    }
    while (1) {
        if (read(*(int*)fd, &t, sizeof(t)) == sizeof(t)) {

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
