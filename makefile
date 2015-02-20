##this is a make file

##******************************************************
##client.h:
	##All the actions will be down in the client
##server.h:
	##Creates the FIFO and the POSIX Message Queue
##substring.h:
	##This is where i will just call the applications of the server and client to run it
##******************************************************

main: client1.c server1.c
	gcc -std=c99 -o client client1.c
	gcc -std=c99 -o server server1.c

clean:
	rm client
	rm server

tar:
	tar -cf Villani-Justin-PA1.tar client1.c server1.c movie.txt makefile