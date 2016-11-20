obj := obj/Login_System
denpend := src/main.c
FLAG := -Iinc -g

all:
	gcc -o $(obj) $(FLAG) $(denpend) -lpthread
clean:
	rm obj/*