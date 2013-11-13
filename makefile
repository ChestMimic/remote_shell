all:
	gcc createThread.c -pthread -o serverCheckpoint
	gcc Project1_Starter_Client.c -o client
