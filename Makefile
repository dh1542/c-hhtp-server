CC=gcc
CFLAGS=-I.

main: main.o
	$(CC) -o main main.o

show_ip: show_ip.o
	$(CC) -o show_ip show_ip.o