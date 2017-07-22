CFLAGS = -g -c -ansi -pedantic -Wall -Werror -g -c
CC = gcc

CLIENT: client_code.c
	$(CC) -o client client_code.c

SERVER: server_code.c
	$(CC) -o server server_code.c

client :
	rm -f CLIENT
	make CLIENT
	./client

serve :
	rm -f SERVER
	make SERVER
	./server
