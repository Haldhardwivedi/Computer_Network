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
	int s_sock;
	double ans;
	int n1,n2,ch;
	s_sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server ,client;
	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr=INADDR_ANY;
	bind(s_sock,(struct sockaddr*)&server,sizeof(server));
	socklen_t client_len;
	client_len=sizeof(client);
	recvfrom(s_sock, &n1, sizeof(n1), 0, (struct sockaddr*)&client,&client_len);
	printf("num1 %d\n",n1);
	recvfrom(s_sock,&n2, sizeof(n2), 0, (struct sockaddr*)&client,&client_len);
	printf("num2 %d\n",n2);
	printf("choices availabel \n");
    printf("1.add\n");
    printf("2.sub\n");
    printf("3.mult\n");
    printf("4.div\n");
    printf("5.modular\n");
	recvfrom(s_sock,&ch,sizeof(ch), 0, (struct sockaddr*)&client,&client_len);
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
	sendto(s_sock,&ans,sizeof(ans), 0, (struct sockaddr*)&client,sizeof(client));
	close(s_sock);
	return 0;
}