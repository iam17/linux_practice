.PHONY:all
all: receive send

receive:receive.c
	gcc -o $@ $^
send:msgsend.c
	gcc -o $@ $^

.PHONY clean:
	rm -rf receive send
