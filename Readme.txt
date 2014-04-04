To compile the code, use the command
	make all
Ignore the warnings that appear, they do not affect the code


The code was started from preexisting code I have written for Networks (CS 3516) that originally acted as an http client/server.
The original code was based on the Beej's guide as well as input from Professor Breecher.

run client
	./client <domain || IP> <port> <file>
known issues with client:
	-does not print out large files correctly all the time, appears to occasionally fragment
	-loops at end of file recieve completion, must be ctrl+c'd out

	
run server
	./server <port>
known issues with server:
	-can not send binary files. Attempting to do so segfaults. I have no idea how this is fixed.
