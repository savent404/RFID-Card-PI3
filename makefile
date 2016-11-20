obj := obj/Login_System
denpend := src/main.c
FLAG := -Iinc -g -std=c99

all:
	gcc -o $(obj) $(FLAG) $(denpend) -lpthread
clean:
	rm obj/*