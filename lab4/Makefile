all:
	gcc dhe.c -lcrypto -o dhe
	gcc dhe_server.c -lcrypto -o dhe_server

start_client:
	./dhe

start_server:
	./dhe_server

clean:
	rm dhe dhe_server


