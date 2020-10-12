#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>    
#include <time.h>
#include <sys/types.h> 
#include<sys/wait.h> 

int main()
{
    int sock,c_sock;
    struct sockaddr_in server,client;
    memset(&server,0,sizeof(server));
    memset(&client,0,sizeof(client));
    socklen_t sLen,cLen;
    sLen = sizeof(server);
    cLen = sizeof(client);
    
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(9261);
    
    if((sock = socket(AF_INET,SOCK_DGRAM,0)) < 0 )
    {
        printf("Socket creation failed\n");
        return 100;
    }
    
    if( (bind(sock,(struct sockaddr *)&server,sLen)) < 0)
    {
        printf("Bind Failure\n");
        return 2000;
    }
    
    char ch,buff[100];
    long long sizeOfFile,n;
    
    //recieved filename from client
    n = recvfrom(sock,&buff,sizeof(buff),0,(struct sockaddr *)&client,&cLen);
    buff[n] = '\0';
    
    printf("The name of file recieved is %s\n",buff);
    
    //recieve file size
    recvfrom(sock,&sizeOfFile,sizeof(sizeOfFile),0,(struct sockaddr *)&client,&cLen);
    printf("Size of file to be recieved is %lld\n",sizeOfFile);
    
    //Create the file
    FILE *fp = fopen(buff,"wb");
    if(fp == NULL)
    {
        printf("Problem in creating file\n");
        return 3000;
    }
    
    //keep writing the sizeoffile characters
    
    n = sizeOfFile;
    
    while(n--)
    {
        recvfrom(sock,&ch,sizeof(ch),0,(struct sockaddr *)&client,&cLen);
        fputc(ch,fp);
       
    }
    
    printf("File recieved successfully\n");    
    close(sock);
    fclose(fp);
    return 0;
}