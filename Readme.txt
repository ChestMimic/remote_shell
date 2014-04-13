Mark FItzgibbon HW 2
mwfitzgibbon
username and password are hardcoded into the program


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
	
known issues:
	seems to disconnect at second client attempt, don't know why
	
Experiments:
	(Due to time, experiments are not very thorough)
	Latency:
		Minimal latency from ccc machine. (close to 0.03 seconds)
	Time a client command vs same command directly on server: 
		Commands vary only by small amount, probably due to testing on localhost in ccc machines. 
		Client is usually larger, presumably to account for connection latency
	Use time inside of a remote command:
		Time returned is relatively similar to running command directly on server
		
	Analasys:
		The environment I have to test is not an ideal testing environment, since variances in network on local machines are small
		presumably, commands usually run around the same average timeframe when the latency time is excluded
		
sample server text:
	./server 8081
8081
socket established
Socket bound.
Listening ...
waiting for next accept
waiting for next accept
mwfitzgibbon
JU
JUbxuwKVStKHI
Passwords match
