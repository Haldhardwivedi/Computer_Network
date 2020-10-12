/*om namah shivay 
Name:haldhar ced18i022
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
int main()
{
    int c_sock ;
    char buf[40];
    int n1,n2,ch;
    double ans;
    c_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(9000);
    client.sin_addr.s_addr = INADDR_ANY;
    if (connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
    {
        printf("failed connection\n");
            return 0;
    }
    recv(c_sock,buf,sizeof(buf),0);
    printf("server :%s\n",buf);
    printf("Enter the first number\n");
    scanf("%d",&n1);
    send(c_sock,&n1,sizeof(n1),0);
    printf("Enter the second number\n");
    scanf("%d",&n2);
    send(c_sock,&n2,sizeof(n2),0);
    printf("enter ur choice\n");
    scanf("%d",&ch);
    send(c_sock,&ch,sizeof(ch),0);
    recv(c_sock,&ans,sizeof(ans),0);
    printf("Result = %f \n",ans );
    close(c_sock);
    return 0;
}