# Client_Server_Application_Sockets
This is using a socket as its form of communication between the server and client.

Programming Assignment 1 (10 pts, Due at 5pm, Feb. 19, Thu.)

Build a client/sever system for movie information retrieval using TCP sockets, which must be able to handle multiple 
concurrent connections. Please use unix system call "fork" to create a child process to serve an incoming connection 
in the server. The server maintains the latest movie information in a file “movie.txt” (posted on the blackboard). 
In the client program, whenever a user inputs a movie title (or part of it), the client program sends the inquiry to 
the server program, the server program searches the file, finds a match and returns the corresponding information 
(Rank, Title, Box Office) to the client program such that the user can see it on the screen. 
If the input text does not match any title in the file, display "No results found!". 
The user should be able to make such an inquiry multiple times during the lifetime of a connection.

Note that:
1) Test both your server and client programs in a single machine, and use IP address “127.0.0.1” (local host) as the 
   server’s IP address and port number "12345" for this service.
   
2) For the grading purpose, you MUST write your programs using C/C++ and put the source code for the client and server 
   programs in files called “client1.c” and “server1.c” respectively. And, you MUST make sure that your programs work on 
   the programming environment that TA described in the recitation.
