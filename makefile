obj := obj/Login_System
denpend := src/main.c
FLAG := -Iinc

all:
	gcc -o $(obj) $(FLAG) $(denpend) -lpthread
clean:
	rm obj/*