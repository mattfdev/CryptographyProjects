all:
	gcc -L/usr/bin dhe.c -o dhe -lcrypto
	gcc -L/usr/bin dhe_server.c -o dhe_server -lcrypto

start_client:
	./dhe

start_server:
	./dhe_server

clean:
	rm dhe dhe_server


