CC=gcc
CCFLAGS=-I.
main: server client

server: server.o
	$(CC) -o $@ $^
	echo "successfull compiled server"

client: client.o
	$(CC) -o $@ $^
	echo "successfull compiled client"
