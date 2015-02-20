/* ======================================================> server1.c 
 * Generic sort of server process for Unix 
 *
 * This is an extremely simple use of sockets for communication.
 * The server opens a socket and then reads messages and prints them out
 * without further ado until the client closes the socket. 
 * =====================================================================
 */

 /**********************************************************************\
*                Copyright (C) Justin Villani, 2014.                   *
*                                                                      *
* This program is free software. You may use, modify, and redistribute *
* it under the terms of the GNU Affero General Public License as       *
* published by the Free Software Foundation, either version 3 or (at   *
* your option) any later version. This program is distributed without  *
* any warranty.                                                        *
\**********************************************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

int sorting_movie_file(int connection_of_client);

int main()
{
   int sock, clientsock, mlen, addrsize, msgct, chc, chct, test=0;
   struct sockaddr_in addr;
   char ch, buf[80];
   char input[30];

   /*
    * Create a socket.
    */

   sock = socket(AF_INET, SOCK_STREAM,0);
   if (sock == -1)
   {   
      perror("opening socket");
      exit(-1);
   }

   /*
    * Bind a name to the socket.  Since the server will bind with
    * any client, the machine address is zero or INADDR_ANY.  The port
    * has to be the same as the client uses.
    */

   addr.sin_family = AF_INET;
   addr.sin_port = htons (12345);
   addr.sin_addr.s_addr = htonl (INADDR_ANY);

   if (bind(sock, (struct sockaddr *) &addr, sizeof (struct sockaddr_in)) == -1) 
   {  
      perror ("on bind");
      exit (-1);
   }

   /*
    * Make the socket available for potential clients.
    */

   if (listen(sock,1) == -1)  
   {  
      perror("on listen");
      exit(-1);
   }

   /*
    * Wait for a client to connect.  When this happens, print out a 
    * message including the address of the client.  Note that clientsock
    * is a socket just like sock, except that it is specifically connected
    * to the client.  sock is used just to get connections.
    */

   addrsize = sizeof(struct sockaddr_in);
   int process;

   for(;;)
   {
            clientsock = accept(sock, (struct sockaddr *) &addr, &addrsize);

            //The connection to the client didn't happen
            if (clientsock == -1)
            {  
                  perror("on accept");
                  exit(-1);
            }

            printf("connection made with client ");
            printf ("%s\n", inet_ntoa (addr.sin_addr));


             //Forking the Client which is coming in
             process = fork();

             if(process < 0)
             {
                perror("It didnt fork");
                exit(1);
             }
             else if(process == 0) //We have entered into the child process
             {
                //This is where i am going to call my function to sort through 
                //client request and print the laues back out to the client

                while(test!=-1)
                {
                  test = sorting_movie_file(clientsock);
                }

                shutdown (clientsock, SHUT_RDWR);
                close(clientsock);
                exit(0);
             }
             else
             {
                close(clientsock);
             }
   }
}

int sorting_movie_file(int connection_of_client)
{
    FILE *pFile;
    char buffer[100];
    char filebuffer[100];
    int message;
    char * found;

    //Opening movie.txt file
    pFile = fopen("movie.txt","r");
    if(pFile == NULL)
    {
      perror("File couldnt open");
    }

    //This is reading from the socket for what the client sent to the server
    message = recv(connection_of_client,buffer,80,0);
    //buffer[message-1]= '\0';

    if (strlen(buffer) == 0)
    {
      fclose(pFile);
      return(1);
    }

    printf("Buffer length: %d\n buffer: %s\n",strlen(buffer), buffer);

    if(message < 0)
    {
      perror("Couldn't read from the socket!!");
    }

    //Ingnoring the firstline
    if(fgets(filebuffer,100,pFile)!=NULL);

    //This has read the file. Ingnoring the first line
    for(int x=0; x<5 ;x++)
    {
        fgets(filebuffer,100,pFile);
        //printf("%s",filebuffer);

        found = strstr(filebuffer,buffer);

        //If it is found then you will send it to the file
        if(found != NULL)
        {
          printf("%s",filebuffer);
          message = send(connection_of_client,filebuffer,strlen(filebuffer)+1,0);
          //printf("%d",message);
          break;
        }
    }

    //This is sending that the file wasnt in there
    if(found == NULL)
    {
      message = write(connection_of_client,"No Results Found\n\n",19);
    }

    if(message < 0)
    {
      perror("Couldn't write to the socket!!");
    }

    fclose(pFile);

    if(strcmp(buffer,"q")==0)
    {
      return(-1);
    }
    else
    {
      return(1);
    }
}
