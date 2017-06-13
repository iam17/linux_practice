.PHONY:all
all:  client server

client:client.c
	gcc -o $@ $^ shm.h
server:server.c
	gcc -o $@ $^ shm.h
.PHONY clean:
	rm -rf server client
