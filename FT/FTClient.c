#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

void DieWithError(char* errorMessage);

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    unsigned short serv_port;
    char* servIP;
    char fileName[256];
    int fileSize;
    char fileBuf[BUFSIZE];
    FILE* fp;
    int len;

    if((argc < 3) || (argc > 4)){
        fprintf(stderr,"Usage: %s <Server IP> <server PORT> [<file name>]\n",argv[0]);
        exit(1);
    }
    servIP = argv[1];
    fileName = argv[3];
    serv_port = atoi(argv[2]);

    fp = fopen("text.txt","r");
    if(fp == NULL)
        DieWithError("File open error");

    if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) <0)
        DieWithError("socket() failed");
    memset(&serv_addr,0, sizeof(serv_addr));
    serv_addr.sin_faily = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(servIP);
    serv_addr.sin_port = htons(serv_prot);

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
        DieWithError("connect() failed");
    printf("Sending => ##################\n");
    if(send(sock,fileName,256,0) != 256)
        DieWithError("send() sent a different file");
    fseek(fp,0,SEEK_END);
    fileSize = ftell(fp);    

    if(send(sock, fileSize,4,0) != 4)
        DieWithError("send() sent a different file size");
    
    while(feof(fp)){
        len = fread(fileBuf, sizeof(char), BUFSIZE,fp);
        send(sock,fileBuf,BUFSIZE,0);
    }
    printf("%s(%d bytes) uploading success to %s",fileName,fileSize,servIP);
    close(fp);
    close(sock);
    exit(0);

}   