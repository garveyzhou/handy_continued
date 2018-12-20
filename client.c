#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  while(1){
    char command[40];
    char received[40];
    printf("[client]:");
    fgets(command,40,stdin);
    write(to_server,command,40);
    read(from_server,received,40);
    printf("[client]:server sends %s \n",received);
  }
}

