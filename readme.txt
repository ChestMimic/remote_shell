To compile the code, use the command
	make all
Ignore the warnings that appear, they do not affect the code

run client
	./client <domain || IP> <port> <file>
known issues with client:
	-does not print out large files correctly all the time, appears to occasionally fragment
	-loops at end of file recieve completion, must be ctrl+c'd out

	
run server
	./server <port>
known issues with server:
	-can not send binary files. Attempting to do so segfaults. I have no idea how this is fixed.
