CC=gcc
CCFLAGS=-I.
DEPS = massage_helper.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

main: server client

server: server.o massage_helper.o
	$(CC) -o $@ $^
	echo "successfull compiled server"

client: client.o massage_helper.o
	$(CC) -o $@ $^
	echo "successfull compiled client"
