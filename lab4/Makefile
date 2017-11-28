all:
	gcc -L/usr/local/lib -lcrypto dhe.c -o dhe
	gcc -L/usr/local/lib -lcrypto dhe_server.c -o dhe_server

start_client:
	./dhe

start_server:
	./dhe_server

clean:
	rm dhe dhe_server


