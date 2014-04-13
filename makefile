all:
	gcc createThread.c -pthread -o server -lcrypt
	gcc http_client.c -o client -lcrypt
