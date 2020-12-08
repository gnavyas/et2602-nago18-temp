all: client server

server.o: server.c
	gcc -c server.c
	
client.o: client.c
	gcc -c client.c

server: server.o
	gcc -o server server.o
	
client: client.o
	gcc -o client client.o


clean:
	rm *.o
