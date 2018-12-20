#include "pipe_networking.h"
#include <signal.h>
static void sighandler(int signo){
	if(signo == SIGINT){
		remove("WKP");
		exit(0);
	}
}

int main() {
	signal(SIGINT,sighandler);
	int to_client;
	char buf[40];
	int from_client= server_handshake( &to_client);
	char extra[5] = "desu";
  	while(1){
		read(from_client,buf,40);
		printf("[Server]:Received %s \n",buf);
		buf[strlen(buf) - 1] = "-";
		strcat(buf,extra);
		write(to_client,buf,40);
		printf("[Server]:Sending %s\n",buf);
	}
	printf("[Server]:End\n");
}
