main: main.c ngui.c
	gcc -Wall ngui.c main.c -o main -l ncurses
