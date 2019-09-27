#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RCVBUFSIZE 32

void DieWithError(char* errorMessage);

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in from_addr;
    unsigned short echoServPort;
    char *servIP;
    char *echoString;
    char echoBuffer[RCVBUFSIZE];
    unsigned int echoStringLen;
    int str_len, addr_size;
    char input[1000];
    char IP[100];
     
    printf("IP : ");
    scanf("%s", IP);
    printf("PORT : ");
    scanf("%hd", &echoServPort);
    servIP = IP;
//    if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
//        DieWithError("socket() failed");
    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        DieWithError("socket() failed");
    
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

//    if(connect(sock, (struct sockaddr *)&echoServAddr,sizeof(echoServAddr)) < 0)
//        DieWithError("connet() failed");

    getchar();
    for(;;) {
        printf("Send : ");
        fgets(input, 1000, stdin);

        if(strcmp(input, "/quit\n") == 0) {
            close(sock);
            exit(0);
        }

        echoString = input;
        echoStringLen = strlen(echoString);
//       if(send(sock,echoString, echoStringLen-1, 0) != echoStringLen-1)
//           DieWithError("send() sent a different number of bytes than expected");

        sendto(sock, echoString, strlen(echoString),0,(struct sockaddr*)&echoServAddr,sizeof(echoServAddr));
        addr_size = sizeof(from_addr);
        
        str_len = recvfrom(sock, echoBuffer, RCVBUFSIZE, 0, (struct sockaddr*)&from_addr,&addr_size);

        echoBuffer[str_len] = 0;
        printf("Received : %s",echoBuffer);

        printf("\n");
    }
 //   close(sock);
 //   exit(0);
}
