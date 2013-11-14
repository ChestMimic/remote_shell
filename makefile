all:
	gcc createThread.c -pthread -o server
	gcc http_client.c -o client
