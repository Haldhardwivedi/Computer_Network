#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>    
#include <time.h>
#include <sys/types.h> 
#include<sys/wait.h> 


int main(int argc, char *argv[])
{
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        printf("socket creation failed\n");
        return 0;   
    }
    struct sockaddr_in server;
    
    memset(&server,0,sizeof(server));
    socklen_t sLen = sizeof(server);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(9261);
    
    char ch,filename[100];
    long long FileSize;
    if (argc < 2) 
    {
        printf("Enter file name to send: ");
            gets(filename);
    }
    else
        strcpy(filename,argv[1]);
    FILE *fp = fopen(filename,"rb");
    if(fp == NULL)
    {
        printf("Erro in opening file\n");
        return 500;
    }
    printf("Name of file to be sent is %s\n",filename);
    //send file name
    time_t t1,t2;
    t1=time(NULL);
    sendto(sock,filename,sizeof(filename),0,(struct sockaddr *)&server,sLen);
    fseek(fp,0L,SEEK_END);  
    FileSize = ftell(fp);
    fseek(fp,0L,SEEK_SET);
    printf("Size of file to be sent is %lld\n",FileSize);
    sendto(sock,&FileSize,sizeof(FileSize),0,(struct sockaddr *)&server,sLen);
    while(FileSize--)
    {
            //adding delay
            for(int i = 0;i < 1000; i++)
            {
                i++;
                i--;
            }
        ch = fgetc(fp);
    
        sendto(sock,&ch,sizeof(ch),0,(struct sockaddr *) &server,sLen);
        
    }
    printf("File sent successfullly\n");
    t2=time(NULL);
    printf("time taken is %ld \n",t2-t1);
    fclose(fp); 
    close(sock);
    return 0;
}
