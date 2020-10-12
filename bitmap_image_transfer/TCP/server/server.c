#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>    
#include <time.h>
#include <sys/types.h> 
#include<sys/wait.h> 

void* Sendimgtoclient(int *arg)
{
            int connfd=(int)*arg;
            FILE *fp = fopen("image.bmp","rb");
            if(fp==NULL)
            {
                printf("File opern error");
                exit(1);  
            }
            long long int count=0;
            clock_t start,end;
            start=clock();
            while(1)
            {
                unsigned char buff[1024]={0};
                int nread = fread(buff,1,1024,fp);
                 if(nread > 0)
                 {
                    write(connfd, buff, nread);
                    count=count+1024;
                 }
                if (nread < 1024)
                {
                     if (feof(fp))
                    {
                         printf("End of file\n");
                         end=clock();
                         printf("----Sent data = %lld bytes\n", count);
                         printf("----Latency: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
                    }
                     if (ferror(fp))
                         printf("Error reading\n");
                        break;
                }
            }
    close(connfd);
}
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    //creating socek
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9000);
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    //opening binary file 
    Sendimgtoclient(&client_sock);
    return 0;
}
