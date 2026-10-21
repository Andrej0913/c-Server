CC=gcc
CCFLAGS=-I.
SQLITE3= -lsqlite3
DEPS = massage_helper.h socket_helper.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

main: server client

server: server.o massage_helper.o socket_helper.o
	$(CC) -o $@ $^ $(SQLITE3)
	echo "successfull compiled server"

client: client.o massage_helper.o socket_helper.o
	$(CC) -o $@ $^
	echo "successfull compiled client"
