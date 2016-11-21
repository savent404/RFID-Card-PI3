#include <main.h>

static struct config config_info = {.input_path = DEFAULT_INPUT_PATH,.output_path = ""};
int main(int argc, char *argv[]) {
    int res = -1;
    pthread_t thread_input, thread_output;
    
    if (argc != 1) {
        for (int i = 1; i < argc; i++) {
            /* Para: help */
            if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
                fprintf(stdout, "There is no help, help yourself\n");
                return 0;
            }
            /* Para: -config */
            if (!strcmp(argv[i], "-config")) {
                i += 1;
                if (argc <= i) {
                    /* use default path:"./config" */
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
    
    /* IO init */
    system("./LoginServe.sh start");

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
static void usr_login(int fd) {
    time_t T;
    char buf[100] = "##System Login:    ";
    char buf_[100];
    strcpy(buf_, asctime(localtime(&T)));
    strcat(buf, buf_);
    write(fd, buf, strlen(buf));
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
        pt += line_cnt;
        line_cnt = 0;
    }
    close(fd);
    return 0;
}

static int  info_get(struct info *pt) {
    time_t T;
    sscanf(pt->src, "%s", pt->out);
    if (strlen(pt->out) != 10) {
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

static void *usr_putc(void* null) {
    
    char buf = 0;
    struct info F;
    int std_out = STDOUT_FILENO;
    int in = open(FIFO_NAME, O_RDONLY|O_NONBLOCK);
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
    usr_login(std_out);

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
        write(std_out, F.out, F.o_num);
        IO_open(std_out);
    }
    exit(-1);
}
static void IO_open(int fd_out) {
    
    char buf[100];

    /* call LoginServe.sh */
    strcpy(buf, "/home/pi/Documents/RFID-Card-PI3/LoginServe.sh open >>");
    strcat(buf, config_info.output_path);
    system(buf);
    strcpy(buf, "/home/pi/Documents/RFID-Card-PI3/LoginServe.sh check >>");
    strcat(buf, config_info.output_path);
    system(buf);
    /* target reset */
//    dup2(old_fd, STDOUT_FILENO);
}
static void *usr_getc(void *null) {
    char buf = 0;
    struct input_event t;
    int fd = open(config_info.input_path, O_RDONLY|O_NONBLOCK);
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
