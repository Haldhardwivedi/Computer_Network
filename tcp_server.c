#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main()
{
    int s_sock , c_sock;
    double ans;
    char buf[40]="Hello Client" ;
    int n1,n2,ch;
    s_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server , client;
    memset(&server,0,sizeof(server));
    memset(&client,0,sizeof(client));
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);
    server.sin_addr.s_addr = INADDR_ANY;
    socklen_t add;
    if (bind(s_sock,(struct sockaddr*)&server,sizeof(server))==-1)
    {
        printf("Server busy\n");
            return 0;
    }
    listen(s_sock,100);
    add = sizeof(client);
    c_sock = accept(s_sock,(struct sockaddr*)&client,&add);
    send(c_sock,buf,sizeof(buf),0);
    recv(c_sock,&n1,sizeof(n1),0);
    printf("num 1 %d\n",n1);
    recv(c_sock,&n2,sizeof(n2),0);
    printf("num 2 %d\n",n2);
    printf("choices availabel \n");
    printf("1.add\n");
    printf("2.sub\n");
    printf("3.mult\n");
    printf("4.div\n");
    printf("5.modular\n");
    recv(c_sock,&ch,sizeof(ch),0);
    switch(ch)
    {
        case 1: ans = n1+n2;
                break;
        case 2: ans = n1-n2;
                break;
        case 3: ans = n1*n2;
                break;
        case 4: ans = n1/n2;
                break;
        case 5: ans = n1%n1;
                break;
        default :printf("Invalid operation\n");
    }
    send(c_sock,&ans,sizeof(ans),0);
    close(s_sock);
    return 0;
}