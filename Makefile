CCFLAGS=-g

all: clean daemon ping_client ping_server

daemon:
	gcc $(CCFLAGS) source/daemon/*.c -o bin/daemon

ping_client:
	gcc $(CCFLAGS) source/ping_client/*.c -o bin/ping_client

ping_server:
	gcc $(CCFLAGS) source/ping_server/*.c -o bin/ping_server

clean:
	rm -f bin/daemon
	rm -f bin/ping_client
	rm -f bin/ping_server
