#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5
#define BUFSIZE 1024

void DieWithError(char* errorMessage);

int main(){
    int serv_sock;
    int clnt_sock;
    unsigned int clntLen;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    unsigned short serv_port;
    char fileName[256];
    int fileSize;
    FILE* fp;

    if(argc != 2){
        fprintf(stderr, "Usage : %s <server Port>\n",argv[0]);
        exit(1);
    }

    serv_port = atoi(argv[1]);
    if((serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
        DieWithError("socket() failed");
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_faily = AF_INET;
    serv_addr.sin_addr.s_addr = hotnl(INADDR_ANY);
    serv_addr.sin_port = htons(serv_port);

    if(bind(serv_sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
        DieWithError("bind() failed");
    if(listen(serv_sock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    
    for(;;){
        clntLen = sizeof(clnt_addr);
        if(clnt_sock = accept(servSock, (struct sockaddr*)&clnt_addr,&clntLen)<0)
            DieWithError("accept() failed");
        printf("Handling client %s\n", inet_ntoa(clnt_addr.sin_addr));
        

    }
}