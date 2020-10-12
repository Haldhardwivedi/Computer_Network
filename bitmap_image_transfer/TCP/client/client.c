#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>    
#include <time.h>
#include <sys/types.h> 
#include<sys/wait.h> 
 int main(int argc, char const *argv[])
{
    int cfd;
    long long int bytesReceived = 0;
    //socket creation starts
    cfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family=AF_INET;
    client.sin_port=htons(9000);
    client.sin_addr.s_addr=inet_addr("127.0.0.10");
    //socket creation ends
    if(connect(cfd,(struct sockaddr*)&client,sizeof(client))==-1)
    {
        printf("connection error\n");
        exit(1);
    }
    char recvBuff[1024];
    FILE *fp;
	char fname[]="image1.bmp";
	printf("File Name: %s\n",fname);
	printf("Receiving file...");
	fp = fopen(fname, "ab"); 
    if(fp == NULL)
    {
       	 printf("Error opening file");
         return 1;
    }
    while((bytesReceived = read(cfd, recvBuff, 1024)) > 0)
    { 
		fflush(stdout);
        fwrite(recvBuff, 1,bytesReceived,fp);
    }
    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }
    printf("\nFile OK....Recieved\n");
	close(cfd);
    printf("Recieved data = %lld bytes\n", bytesReceived);
    return 0;
}