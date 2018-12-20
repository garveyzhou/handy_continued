#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
	char buf[200];

	//creating pipe
	mkfifo("WKP",0644);
	printf("[server]:Waiting for connection...\n");
	int public = open("WKP",O_RDONLY);
	//receive
	read(public,buf,20);
	printf("[server]:Message %s received\n",buf);

	//writing to private
	int privatep = open("private",O_WRONLY);
	write(privatep,ACK,sizeof(ACK));
	*to_client = privatep;
	read(public,buf,200);
	if(!(strcmp(buf,"Got Client"))){
		printf("[server]:Handshake Completed\n");
	}
	return public;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
	char buf[200];
	char * name = "private";
	//Create Pipe
	mkfifo(name,0644);

	//Write to server
	int public = open("WKP",O_WRONLY);
	printf("[client]:Open WKP\n");
	write(public,buf,20);

	//Opening private pipe
	int private = open(name,O_RDONLY);
	printf("[client]:Open private pipe\n");

	read(private,buf,200);

	printf("[client]:Message Received %s\n",buf);
	
	//Final check
	write(public,"Got Client",200);
	*to_server = public;
  	return private;
}
